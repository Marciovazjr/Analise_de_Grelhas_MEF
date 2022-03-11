#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <math.h>

int main(int argc, char * argv[])
{
  int modelo;
  int exemp;
  int nos;
  int barras;
  int material;
  int geometria;
  int forca;
  int forca_nos;
  int restricao[30][5];
  int vinculos [50][10];
  int coordenadas[30][5];
  float parametGeometrico[10][10];
  float constanteGeometrica [10][10];
  float constanteMaterial [10][5];
  float constanteMat[10][5];
  float forcaExterna [20][10];
  float forcaNos [20][10];
  int i;

  float constG;
  float p_d;
  float p_b,p_h;
  float p_hh,p_bb,p_eb,p_eh;
  float alpha,termoD;

  FILE *mod = fopen("1_modelo.txt","r");

  // lendo exemplo
  fscanf(mod, "%d", &exemp);

  // lendo modelo (consideraçao dos deslocamentos dos esforços cortantes)
  fscanf(mod, "%d", &modelo);

  // lendo no
  fscanf(mod, "%d", &nos);

  // lendo barras
  fscanf(mod, "%d", &barras);

  // lendo as coordenadas dos pontos, 1 por linha
  for (i = 0; i < nos; i++){
    for (int j = 0; j < 2; j++){
        fscanf(mod,"%d",&coordenadas[i][j]);
    }
  }

  // lendo as restrições para cada grau de liberdade dos pontos, 1 por linha
  for (i = 0; i < nos; i++){
    for(int j = 0; j < 3; j++){
        fscanf(mod, "%d", &restricao[i][j]);
    }
  }

   // lendo os vinculos entre cada barra, 1 por linha (Atribuir as relativas aos materiais e geometria para cada barra)
  for (i = 0; i < barras; i++){
      for(int j = 0; j < 5; j++){
        fscanf(mod,"%d", &vinculos[i][j]);
    }
  }

  // lendo quant. material
  fscanf(mod, "%d", &material);

   // lendo o numero de material participantes da simulação
   for (i = 0; i < material; i++){
    for (int j = 0; j < 2;j++){
        fscanf(mod,"%f",&constanteMat[i][j]);
    }
  }

  // lendo quant. geometria
  fscanf(mod, "%d", &geometria);

  // lendo o numero de geometrias participantes da simulação
  for (i = 0; i < geometria; i++){
    for (int j = 0; j < 5;j++){
        fscanf(mod,"%f",&parametGeometrico[i][j]);
    }
  }

  // lendo quant. força
  fscanf(mod, "%d", &forca_nos);

  // lendo os esforços participantes da simulação
   for (i = 0; i < forca_nos; i++){
     for (int j = 0; j < 4;j++){
        fscanf(mod, "%f",&forcaNos[i][j]);
    }
  }

  // lendo quant. força
  fscanf(mod, "%d", &forca);

  // lendo os esforços participantes da simulação
   for (i = 0; i < forca; i++){
     for (int j = 0; j < 6;j++){
        fscanf(mod, "%f",&forcaExterna[i][j]);
    }
  }
  fclose(mod);

  // Relatorio elaborado a partir dos dados informados
  FILE *arq = fopen("2_imput.txt","w");

  fprintf(arq,"            MODELO COMPUTACIONAL           \n");
  fprintf(arq,"                   PARA           \n");
  fprintf(arq,"       ANÁLISE MATRICIAL DE ESTRUTURAS          \n");
  fprintf(arq,"                 (GRELHAS)         \n\n");

  fprintf(arq,"        Dados gerais da estrutura          \n");
  fprintf(arq,"Nº do exemplo: %d  \n",exemp);
  fprintf(arq,"Considerar o efeito do esforço cortante: %d    \t OBS: 0 - Não | 1 - Sim \n",modelo);
  fprintf(arq,"Nº de nos: %d  \n",nos);
  fprintf(arq,"Nº de barras: %d  \n",barras);
  fprintf(arq,"Nº de propriedades materias que compoem a estrutura: %d  \n",material);
  fprintf(arq,"Nº de propriedades geometricas que compoem a estrutura: %d  \n\n",geometria);

  fprintf(arq,"############# Coordenadas #############\n");
  fprintf(arq,"\n");
  fprintf(arq,"Nº do nos        Eixo X        Eixo Z\n");
  for (int i = 0; i< nos; i++){
    fprintf(arq," %d                %d              %d \n",i+1,coordenadas[i][0],coordenadas[i][1]);
  }
  fprintf(arq,"\n");
  fprintf(arq,"#################### Restricoes ####################\n");
  fprintf(arq,"\n");
  fprintf(arq,"Nº do nos        Eixo y       Eixo x      Eixo z\n");
  for (int i = 0; i< nos; i++){
    fprintf(arq," %d                %d              %d          %d\n",i+1,restricao[i][0],restricao[i][1],restricao[i][2]);
  }
  fprintf(arq,"\n");
  fprintf(arq,"OBS: 0: livre | 1 : restrito");

  fprintf(arq,"\n\n");

  fprintf(arq,"################################################# Propriedades dos materiais #################################################  \n");
  fprintf(arq,"\n");
  fprintf(arq,"Material          Modulo de elasticidade (E) [KPa]          Coeficiente de Poisson        Modulo de cisalhamento (G) [KPa]\n ");
  for(int i = 0;i<material;i++){
    constanteMaterial[i][0] = constanteMat[i][0];
    constG = constanteMat[i][0]/(2*(1+constanteMat[i][1]));
    constanteMaterial[i][1] = constG;

    fprintf(arq," %d                       %.0f                                   %.2f                         %.2f \n",i+1,constanteMaterial[i][0],constanteMat[i][1],constanteMaterial[i][1]);
  }

  fprintf(arq,"\n\n");

  fprintf(arq,"################################# Parametros geometricos ################################# \n ");
  fprintf(arq,"\n");
  fprintf(arq,"Secao     Tipo      Largura [m]         Altura [m]       Espessura 1 [m]    Espessura 2 [m] \n");
  for(int i = 0;i < geometria;i++){
        fprintf(arq,"%d           %.0f          %.4f             %.4f              %.4f            %.4f \n",i+1,parametGeometrico[i][0],parametGeometrico[i][1],parametGeometrico[i][2],parametGeometrico[i][3],parametGeometrico[i][4]);
  }

  fprintf(arq,"\n");

  fprintf(arq,"Para o tipo de secao(1): Circular \n");
  fprintf(arq,"Para o tipo de secao(2): Retangular \n");
  fprintf(arq,"Para o tipo de secao(3): Perfil em I \n");

  fprintf(arq,"\n\n");

  fprintf(arq,"####################################################################### Propriedades da geometria ###################################################################### \n ");
  fprintf(arq,"\n");
  fprintf(arq,"Secao     Tipo     Area da sec. transv. [m2]          Momento de inercia a flexão(I) [m4]          Momento de inercia a torção (J) [m4]        Fator de cisalhamento(f) \n");
  for(int i = 0;i < geometria;i++){
      if (parametGeometrico[i][0]==1){
          constanteGeometrica[i][0] = parametGeometrico[i][0];
          p_d = parametGeometrico[i][1];
          constanteGeometrica[i][1] = M_PI*pow(p_d,2)/4.;     //Area
          constanteGeometrica[i][2] = M_PI*pow(p_d,4)/64.;    //Momento de inercia
          constanteGeometrica[i][3] = M_PI*pow(p_d,4)/32.;    //Momento de inercia polar
          constanteGeometrica[i][4] = 10./9.;                 //Fator de cisalhamento
      }
      if (parametGeometrico[i][0]==2){
          constanteGeometrica[i][0] = parametGeometrico[i][0];
          p_b = parametGeometrico[i][1];
          p_h = parametGeometrico[i][2];
          constanteGeometrica[i][1] = p_b*p_h;
          constanteGeometrica[i][2] = (p_b*pow(p_h,3))/12.;
          constanteGeometrica[i][3] = (p_h*pow(p_b,3))*((1./3.)-(0.21*(p_b/p_h)*(1 - pow(p_b,4)/(12*pow(p_h,4)))));
          constanteGeometrica[i][4] = 6./5.;
      }
      if (parametGeometrico[i][0]==3){
          constanteGeometrica[i][0] = parametGeometrico[i][0];
          p_bb = parametGeometrico[i][1];
          p_hh = parametGeometrico[i][2];
          p_eb = parametGeometrico[i][3];
          p_eh = parametGeometrico[i][4];
          constanteGeometrica[i][1] = (p_hh-p_eb)*p_eh + 2.*p_bb*p_eb;
          constanteGeometrica[i][2] = (p_eh*(pow((p_hh-2.*p_eb),3))/12.)+(p_bb*p_eb*(pow((p_hh-p_eb),2))/2.)+(p_bb*pow(p_eb,3)/6.);
          alpha = -0.042+0.2204*(p_eh/p_eb)-0.0725*(pow(p_eh,2)/pow(p_eb,2));
          termoD = (pow(p_eb,2)+(p_eh*(p_eh/4)))/p_eb;
          constanteGeometrica[i][3] = (1./3.)*((p_hh-2*p_eb)*pow(p_eh,3)+2*p_bb*pow(p_eb,3))-0.42*(pow(p_eb,4))+2*alpha*pow(termoD,4);
          constanteGeometrica[i][4] = constanteGeometrica[i][1]/((p_hh-p_eb)*p_eh);
      }
      fprintf(arq,"%d           %.0f            %.4f                              %.10f                                   %.10f                                      %.2f\n",i+1,constanteGeometrica[i][0],constanteGeometrica[i][1],constanteGeometrica[i][2],constanteGeometrica[i][3],constanteGeometrica[i][4]);
  }

  fprintf(arq,"\n\n");

  fprintf(arq,"#################################### Vinculos ####################################\n ");
  fprintf(arq,"\n");
  fprintf(arq,"Barra    Nó (inicial)    Nó (final)   Artic. (Grau de lib)   Material      Secao\n");
  for(int i = 0;i < barras;i++){
    fprintf(arq,"  %d            %d             %d               %d                  %d            %d \n",i+1,vinculos[i][0],vinculos[i][1],vinculos[i][4],vinculos[i][2],vinculos[i][3]);
  }
  fprintf(arq,"\n");
  fprintf(arq,"Se Artic. (Grau de lib) = 0, nao ha articulacao na barra");

  fprintf(arq,"\n\n");

  fprintf(arq,"################################### Cargas (Nos) ################################### \n ");
  fprintf(arq,"\n");
  fprintf(arq,"Nó           Eixo Y (V)[KN]             Eixo X (T)[KN.m]           Eixo Z (M)[KN.m]\n");
  for(int i = 0;i < forca_nos;i++){
    fprintf(arq," %.0f                %.2f                        %.2f                    %.2f \n",forcaNos[i][0],forcaNos[i][1],forcaNos[i][2],forcaNos[i][3]);
  }

  fprintf(arq,"\n\n");

  fprintf(arq,"################################################ Cargas Externas (Barra) ################################################\n ");
  fprintf(arq,"\n");
  fprintf(arq,"Barra       Tipo de carga    Intensidade(F,M,w ou w1)      Intensidade(w2)      Distancia(l1) [m]       Distancia(l2) [m]\n");
  for(int i = 0;i < forca;i++){
    fprintf(arq,"  %.0f             %.0f                    %.2f                    %.2f                   %.2f                  %.2f \n",forcaExterna[i][0],forcaExterna[i][1],forcaExterna[i][2],forcaExterna[i][3],forcaExterna[i][4],forcaExterna[i][5]);
  }
  fprintf(arq,"\n");
  fprintf(arq,"Para o tipo de carga(1): Carga pontual \n");
  fprintf(arq,"Para o tipo de carga(2): Momento fletor \n");
  fprintf(arq,"Para o tipo de carga(3): Carga distribuida constante \n");
  fprintf(arq,"Para o tipo de carga(4): Carga distribuida trapezoidal \n");
  fprintf(arq,"Para o tipo de carga(5): Momento torçor \n");

  fclose(arq);

 float Rigidezlocal_sem_rot[50][10][10];
 float Rigidez_artic[50][10][10];
 float MatrizTransf [50][10][10];
 float MatrizTransfTranspost [50][10][10];
 float Rigidezbarra [50][10][10];
 float mult[50][10][10];  // Matriz auxiliar no produto matricial T(^T)*K*T

 float mod_e,mod_g,mod_i,mod_j;
 int no_i,no_f;
 int mat,geo;
 int x_i,x_f,dx;
 int z_i,z_f,dz;
 float L;
 float termo1,termo2,termo3,termo4,termo5;
 float cos,sen;
 int l;
 float valor;
 float fator,area,cort;

 //Determinar a matriz de rigidez de cada barra
 for(int i = 0; i < barras;i++){
      mat = vinculos[i][2];
      geo = vinculos[i][3];

      mod_e = constanteMaterial[mat-1][0];
      mod_g = constanteMaterial[mat-1][1];
      mod_i = constanteGeometrica[geo-1][2];
      mod_j = constanteGeometrica[geo-1][3];
      fator = constanteGeometrica[geo-1][4];
      area = constanteGeometrica[geo-1][1];

      no_i = vinculos[i][0];
      no_f = vinculos[i][1];

      x_i = coordenadas[no_i-1][0];
      x_f = coordenadas[no_f-1][0];
      dx = x_f - x_i;

      z_i = coordenadas[no_i-1][1];
      z_f = coordenadas[no_f-1][1];
      dz = z_f - z_i;

      L = sqrt(pow(dx,2)+pow(dz,2));

      if (modelo==0){
         cort = 0.0;
      }
      if (modelo==1){
         cort = (12*mod_e*mod_i*fator)/(mod_g*area*(pow(L,2)));
      }

      // Zerar a matriz de rigidez local da barra i
      for (int a = 0; a < 6; a++){
        for(int b = 0; b < 6; b++){
            Rigidezlocal_sem_rot[i][a][b] = 0.0;
            Rigidez_artic[i][a][b]=0.0;
        }
      }

      termo1 = 12*(mod_e*mod_i)/(pow(L,3)*(1+cort));
      termo2 = 6*(mod_e*mod_i)/(pow(L,2)*(1+cort));
      termo3 = (mod_g*mod_j)/L;
      termo4 = (4+cort)*(mod_e*mod_i)/(L*(1+cort));
      termo5 = (2-cort)*(mod_e*mod_i)/(L*(1+cort));

      Rigidezlocal_sem_rot[i][0][0] = termo1;
      Rigidezlocal_sem_rot[i][0][2] = termo2;
      Rigidezlocal_sem_rot[i][0][3] = -termo1;
      Rigidezlocal_sem_rot[i][0][5] = termo2;
      Rigidezlocal_sem_rot[i][1][1] = termo3;
      Rigidezlocal_sem_rot[i][1][4] = -termo3;
      Rigidezlocal_sem_rot[i][2][0] = termo2;
      Rigidezlocal_sem_rot[i][2][2] = termo4;
      Rigidezlocal_sem_rot[i][2][3] = -termo2;
      Rigidezlocal_sem_rot[i][2][5] = termo5;
      Rigidezlocal_sem_rot[i][3][0] = -termo1;
      Rigidezlocal_sem_rot[i][3][2] = -termo2;
      Rigidezlocal_sem_rot[i][3][3] = termo1;
      Rigidezlocal_sem_rot[i][3][5] = -termo2;
      Rigidezlocal_sem_rot[i][4][1] = -termo3;
      Rigidezlocal_sem_rot[i][4][4] = termo3;
      Rigidezlocal_sem_rot[i][5][0] = termo2;
      Rigidezlocal_sem_rot[i][5][2] = termo5;
      Rigidezlocal_sem_rot[i][5][3] = -termo2;
      Rigidezlocal_sem_rot[i][5][5] = termo4;


       for (int a = 0; a < 6; a++){
            for(int b = 0; b < 6; b++){
                Rigidez_artic[i][a][b] = Rigidezlocal_sem_rot[i][a][b];
            }
       }

       l = vinculos[i][4]-1;
       if(l >= 0){
            for (int a = 0; a < 6; a++){
                if(a!=l){
                    valor = Rigidez_artic[i][a][l] / Rigidez_artic[i][l][l];
                    for(int b = 0; b < 6; b++){
                        Rigidez_artic[i][a][b] = Rigidez_artic[i][a][b]-valor*Rigidez_artic[i][l][b];
                    }
                }
            }
            for (int a = 0; a < 6; a++){
                Rigidez_artic[i][l][a] = 0.0;
            }
       }
      // Zerar a matriz de transformação
      for (int a = 0; a < 6; a++){
        for(int b = 0; b < 6; b++){
            MatrizTransf[i][a][b] = 0;
        }
      }

      sen = dz/L;
      cos = dx/L;

      MatrizTransf[i][0][0] = 1.0;
      MatrizTransf[i][1][1] = cos;
      MatrizTransf[i][1][2] = sen;
      MatrizTransf[i][2][1] = -sen;
      MatrizTransf[i][2][2] = cos;
      MatrizTransf[i][3][3] = 1.0;
      MatrizTransf[i][4][4] = cos;
      MatrizTransf[i][4][5] = sen;
      MatrizTransf[i][5][4] = -sen;
      MatrizTransf[i][5][5] = cos;

      //  Matriz de transformação transposta
      for (int a = 0; a < 6; a++){
        for(int b = 0; b < 6; b++){
            MatrizTransfTranspost[i][a][b] = MatrizTransf[i][b][a];
        }
      }

      //Determinar a matriz de rigidez de cada barra no referencial global
       for(int a = 0 ; a <6; a ++) {
            for (int b = 0 ; b <6; b ++) {
                mult[i][a][b] = 0;
                for (int c = 0 ; c <6; c ++) {
                    mult[i][a][b] += MatrizTransfTranspost [i][a][c] * Rigidez_artic[i][c][b];
			    }
            }
	    }

       for(int a = 0 ; a <6; a ++) {
            for (int b = 0 ; b <6; b ++) {
                Rigidezbarra[i][a][b] = 0;
                for (int c = 0 ; c <6; c ++) {
                    Rigidezbarra[i][a][b] += mult [i][a][c] * MatrizTransf[i][c][b];
                }
		    }
	    }
    }

int mapeamento [50][10][10];
int mapglobal [30][5];
int maplocal [10][10];

    for (int a = 0; a < nos;a++){
       for(int b = 0; b < 3;b++){
            mapglobal[a][b] = (3*a)+(b+1);
        }
    }

    //Mapeamento da estrutura
    for (int a = 0; a < barras;a++){
        no_i = vinculos[a][0];
        no_f = vinculos[a][1];

      // Graus de liberdade local
        for (int q = 0; q < 2; q++){
            for(int w = 0;w<3;w++){
                maplocal[q][w] = (3*q)+(w+1);
            }
        }

        for (int q = 0;q<3;q++){
                mapeamento[a][q][0] = maplocal[0][q];
                mapeamento[a][q][1] = mapglobal[no_i-1][q];
            }

        for (int q = 3;q<6;q++){
                mapeamento[a][q][0] = maplocal[1][q-3];
                mapeamento[a][q][1] = mapglobal[no_f-1][q-3];
            }
    }

//Matriz de rigidez da estrutura global (barra)
int grau_lib_total = 3*nos;
float Rigidez[50][80][80];

    // Zerar a matriz de rigidez
    for(int c = 0; c < barras; c ++){
      for (int a = 0; a < grau_lib_total; a++){
        for(int b = 0; b < grau_lib_total; b++){
            Rigidez[c][a][b] = 0.0;
        }
      }
       for (int a = 0; a < 6; a++){
            for(int b = 0; b < 6; b++){
                int loc1 = mapeamento[c][a][0];
                int glob1 = mapeamento [c][a][1];
                int loc2 = mapeamento[c][b][0];
                int glob2 = mapeamento [c][b][1];

                Rigidez[c][glob1-1][glob2-1] = Rigidezbarra[c][loc1-1][loc2-1];
                }
            }
        }

//Matriz de rigidez da estrutura global
float RigidezEstrutura [80][80];

    for (int a = 0; a < grau_lib_total;a++){
        for(int b = 0; b < grau_lib_total; b++){
            float soma = 0;
            for(int c = 0; c < barras; c++){
                soma += Rigidez[c][a][b];
            }
            RigidezEstrutura[a][b] = soma;
        }
    }

//Matriz de rigidez efetiva
float RigidezEfetiva [80][80];
int restLivreGlobal [80];
int livre = 0;
int rest;

    for (int a = 0; a < nos; a++){
        for(int b = 0; b < 3; b++){
            rest = restricao[a][b];
            if (rest == 0){
                livre++;
            }
        }
    }

    int contador = 0;
    while (contador<livre){
        for (int a = 0; a < nos; a++){
            for(int b = 0; b < 3; b++){
                rest = restricao[a][b];
                if (rest == 0){
                    restLivreGlobal[contador] = mapglobal[a][b];
                    contador++;
                }
            }
        }
    }

    for (int a = 0; a < livre; a++){
        for(int b = 0; b< livre; b++){
            RigidezEfetiva[a][b] = RigidezEstrutura[restLivreGlobal[a]-1][restLivreGlobal[b]-1];
        }
    }
//----------------------------------------------------------------------------------------------------------------------

//Exforços externos nas barras (local/global)
float esf_barra_local_no [50][10][5];
float esf_barra_local_carga [50][10][5];
float esf_barra_global_carga [50][10][5];
int grau_lib_esf [50][10][5];


//Força aplicada aos nos do modelo (nos).
    for(int p = 0; p < barras; p++){
        int no_i = vinculos[p][0];
        int no_f = vinculos[p][1];

        //Zerar o vetor coluna das forças
        for (int a = 0; a < 6; a++){
                esf_barra_local_no[p][a][0] = 0.0;
        }

        for (int a = 0; a < 3; a++){
            for (int b = 0; b < forca_nos; b++){
                if (no_i == forcaNos[b][0]){
                        esf_barra_local_no[p][a][0] = forcaNos[b][a+1];
                }
                grau_lib_esf[p][a][0] = mapglobal[no_i-1][a];
            }
        }

        for (int a = 3; a < 6; a++){
            for (int b = 0; b < forca_nos; b++){
                if (no_f == forcaNos[b][0]){
                        esf_barra_local_no[p][a][0] = forcaNos[b][a-2];
                }
                grau_lib_esf[p][a][0] = mapglobal[no_f-1][a-3];
            }
        }
    }

//Força aplicada aos nos do modelo (barras).
int no_if,no_ff;
int x_if,x_ff;
int z_if,z_ff;
int dxf,dzf;
float Lf;
float Wf,w,l1,l2;
float mod_ef,mod_if;
int matf,geof;
int pp;
float valorp;

    for(int p = 0; p < barras; p++){
        no_if = vinculos[p][0];
        no_ff = vinculos[p][1];

        matf = vinculos[i][2];
        geof = vinculos[i][3];

        mod_ef = constanteMaterial[matf-1][0];
        mod_if = constanteGeometrica[geof-1][2];

        x_if = coordenadas[no_if-1][0];
        x_ff = coordenadas[no_ff-1][0];
        dxf = x_ff - x_if;

        z_if = coordenadas[no_if-1][1];
        z_ff = coordenadas[no_ff-1][1];
        dzf = z_ff - z_if;

        Lf = sqrt(pow(dxf,2)+pow(dzf,2));

        for (int a = 0; a < 6; a++){
            esf_barra_local_carga[p][a][0] = 0.0;
        }


        for (int a = 0; a < forca; a++){
            if ((p+1) == forcaExterna[a][0]){
                    Wf = forcaExterna[a][2];
                    w = forcaExterna[a][3];
                    l1 = forcaExterna[a][4];
                    l2 = forcaExterna[a][5];

                    if (forcaExterna[a][1] == 1){
                        esf_barra_local_carga[p][0][0] += ((Wf*pow((Lf-l1),2))/(pow(Lf,3)))*(3*l1+(Lf-l1));
                        esf_barra_local_carga[p][2][0] += (Wf*l1*pow((Lf-l1),2))/(pow(Lf,2));
                        esf_barra_local_carga[p][3][0] += ((Wf*pow(l1,2))/(pow(Lf,3)))*(l1+3*(Lf-l1));
                        esf_barra_local_carga[p][5][0] += (-Wf*(Lf-l1)*pow(l1,2))/(pow(Lf,2));
                    }
                    if (forcaExterna[a][1] == 2){
                        esf_barra_local_carga[p][0][0] += (-6*Wf*l1*(Lf-l1))/(pow(Lf,3));
                        esf_barra_local_carga[p][2][0] += ((Wf*(Lf-l1))/pow(Lf,2))*((Lf-l1)-2*l1);
                        esf_barra_local_carga[p][3][0] += (6*Wf*l1*(Lf-l1))/(pow(Lf,3));
                        esf_barra_local_carga[p][5][0] += ((Wf*l1)/pow(Lf,2))*(l1-2*(Lf-l1));
                    }
                    if (forcaExterna[a][1] == 3){
                        esf_barra_local_carga[p][0][0] += ((Wf*Lf)/2)*(1- (l1/pow(Lf,4))*(2*pow(Lf,3)-2*pow(l1,2)*L+pow(l1,3)) - (pow(l2,3)/pow(Lf,4))*(2*Lf-l2));
                        esf_barra_local_carga[p][2][0] += ((Wf*pow(Lf,2))/12)*(1- (pow(l1,2)/pow(Lf,4))*(6*pow(Lf,2)-8*l1*L+3*pow(l1,3)) - (pow(l2,3)/pow(Lf,4))*(4*Lf-3*l2));
                        esf_barra_local_carga[p][3][0] += ((Wf*Lf)/2)*(1- (pow(l1,3)/pow(Lf,4))*(2*Lf-l1) - (l2/pow(Lf,4))*(2*pow(Lf,3)-2*pow(l2,2)*Lf+pow(l2,3)));
                        esf_barra_local_carga[p][5][0] += ((-Wf*pow(Lf,2))/12)*(1- (pow(l1,3)/pow(Lf,4))*(4*Lf-3*l1) - (pow(l2,2)/pow(Lf,4))*(6*pow(Lf,2)-8*l2*Lf+3*pow(l2,2)));
                    }
                    if (forcaExterna[a][1] == 4){
                        esf_barra_local_carga[p][0][0] += ((Wf*pow((Lf-l1),3))/(20*pow(Lf,3)))*((7*Lf + 8*l1)-((l2*(3*Lf+2*l1))/(Lf-l1))*(1+(l2/(Lf-l1))+(pow(l2,2)/(pow((Lf-l1),2)))) + ((2*pow(l2,4))/(pow((Lf-l1),3)))) + ((w*pow((Lf-l1),3))/(20*pow(Lf,3)))*((3*Lf + 2*l1)*(1+(l2/(Lf-l1))+(pow(l2,2)/pow((Lf-l1),2)))-((pow(l2,3)/pow((Lf-l1),2))*(2+((15*Lf-8*l2)/(Lf-l1)))));
                        esf_barra_local_carga[p][2][0] += ((Wf*pow((Lf-l1),3))/(60*pow(Lf,2)))*((3*Lf + 12*l1)-((l2*(2*Lf+3*l1))/(Lf-l1))*(1+(l2/(Lf-l1))+(pow(l2,2)/(pow((Lf-l1),2)))) + ((3*pow(l2,4))/(pow((Lf-l1),3)))) + ((w*pow((Lf-l1),3))/(60*pow(Lf,2)))*((2*Lf + 3*l1)*(1+(l2/(Lf-l1))+(pow(l2,2)/pow((Lf-l1),2)))-((3*pow(l2,3)/pow((Lf-l1),2))*(1+((5*Lf-4*l2)/(Lf-l1)))));
                        esf_barra_local_carga[p][3][0] += ((Wf+w)/2)*(Lf-l1-l2) - esf_barra_local_carga[p][0][0];
                        esf_barra_local_carga[p][5][0] += ((Lf-l1-l2)/6)*(Wf*(-2*Lf+2*l1-l2)-w*(Lf-l1+2*l2))+ esf_barra_local_carga[p][0][0]*Lf - esf_barra_local_carga[p][2][0];
                    }
                    if(forcaExterna[a][1] == 5){
                        esf_barra_local_carga[p][1][0] += Wf*(Lf-l1)/Lf;
                        esf_barra_local_carga[p][4][0] += Wf*l1/Lf;
                    }
                    if(forcaExterna[a][1] == 6){
                        esf_barra_local_carga[p][2][0] += mod_ef*mod_if*l1*((w-Wf)/l2);
                        esf_barra_local_carga[p][5][0] += mod_ef*mod_if*l1*(-(w-Wf)/l2);
                    }
                }
            }

         pp = vinculos[p][4]-1;
         if(pp >= 0){
             for (int a = 0; a < 6; a++){
                if(a!=pp){
                    valorp = Rigidezlocal_sem_rot[p][a][pp] / Rigidezlocal_sem_rot[p][pp][pp];
                    esf_barra_local_carga[p][a][0] = esf_barra_local_carga[p][a][0] - valorp*esf_barra_local_carga[p][pp][0];
                }
            }
            esf_barra_local_carga[p][pp][0] = 0.0;
        }


        for(int a = 0 ; a <6; a ++) {
                esf_barra_global_carga[p][a][0] = 0.0;
                for (int c = 0 ; c <6; c ++) {
                    esf_barra_global_carga[p][a][0] += MatrizTransfTranspost [p][a][c] * esf_barra_local_carga[p][c][0];
			    }
            }
        }

//Esforços externos
float EsforcoCarga [50][80][5];
float EsforcoExterno [80][5];
float EsforcoNoTotal [80][5];
float EsforcoCargaTotal [80][5];
float EsforcoExternoEfet[80][5];

    for (int p = 0; p < barras; p++){
        for (int a = 0; a < grau_lib_total; a++){
            EsforcoCarga[p][a][0] = 0.0;
        }

        for (int a = 0; a < 6; a++){
            EsforcoCarga[p][(grau_lib_esf[p][a][0]-1)][0] = esf_barra_global_carga[p][a][0];
         }
    }

    for (int a = 0; a < grau_lib_total; a++){
        EsforcoNoTotal[a][0] = 0.0;
        EsforcoCargaTotal[a][0] = 0.0;
    }

    for (int a = 0; a < grau_lib_total; a++){
        for(int p = 0; p < barras; p++){
            EsforcoCargaTotal[a][0] += EsforcoCarga[p][a][0];
        }
    }


    int ponto;
    int grau;
    int aux;
    for(int a = 0; a < forca_nos;a++){
        ponto = forcaNos[a][0];
        grau = 3*ponto-3;
        aux = 1;
        for(int b = grau; b < 3*ponto;b++){
            EsforcoNoTotal[b][0] = forcaNos[a][aux];
            aux++;
        }
    }

    for (int a = 0; a < grau_lib_total; a++){
        EsforcoExterno[a][0] = 0.0;
    }

    for (int a = 0; a < grau_lib_total; a++){
            EsforcoExterno[a][0] = EsforcoNoTotal[a][0] - EsforcoCargaTotal[a][0];
    }

    for (int a = 0; a < livre; a++){
            EsforcoExternoEfet[a][0] = EsforcoExterno[restLivreGlobal[a]-1][0];
        }

//-------------------------------------------------------------------------------------------------------------------------------------
// Matriz ampliada (Rigedez Efetiva + Esforços Externo Efetivo)

float MatrizAmpliada [80][80];

for(int a = 0; a < livre;a++){
    for(int b = 0; b < (livre+1); b++){
        if(b<livre){
            MatrizAmpliada[a][b] = RigidezEfetiva [a][b];
        }else{
            MatrizAmpliada[a][b] = EsforcoExternoEfet[a][0];
        }
    }
}

//Metodo da eliminação de Gauss
float c,somagauss,desl[80];

for(int col = 0; col < livre; col++){
    for(int lin = 0; lin < livre; lin++){
        if (lin>col){
            c = - (MatrizAmpliada[lin][col]/MatrizAmpliada[col][col]);
            for(int k = 0; k < (livre+1);k++){
                MatrizAmpliada[lin][k] = c*MatrizAmpliada[col][k]+MatrizAmpliada[lin][k];
            }
        }
    }
}

//Zera matriz dos deslocamentos

for(int a = 0; a < livre; a++){
    desl[a] = 0.0;
}

desl[livre-1]=MatrizAmpliada[livre-1][livre]/MatrizAmpliada[livre-1][livre-1];

for(int a = livre-2; a >= 0 ; a--){
    somagauss = 0.0;
    for(int b = a+1; b<livre ; b++){
        somagauss = somagauss + MatrizAmpliada[a][b]*desl[b];
    }
    desl[a] = (MatrizAmpliada[a][livre] - somagauss)/MatrizAmpliada[a][a];
}

//-----------------------------------------------------------------------------------------------------------------------------------------
//Deslocamentos
float Deslocglob [80][5];
float desloc = 1.0;

    for (int a = 0; a < grau_lib_total; a++){
        for(int b = 0; b < 1; b++){
            Deslocglob[a][b] = desloc;
        }
    }

    int t = 0;
    for (int a = 0; a < nos; a++){
        for(int b = 0; b < 3 ; b++){
            if (restricao[a][b]==1){
                Deslocglob[t][0] = 0.0;
            }
            t++;
        }
    }

    int r = 0;
    for (int a = 0; a < grau_lib_total; a++){
           if (Deslocglob[a][0] != 0.0){
                Deslocglob[a][0] = desl[r];
                r++;
           }
    }

//Deslocamentos das barras
float Deslbarglob [50][10][5];
float Deslbarloc [50][10][5];

 for (int p = 0; p < barras; p++){
        for (int a = 0; a < 6; a++){
            Deslbarglob[p][a][0] = 0.0;
        }

        for (int a = 0; a < 6; a++){
            Deslbarglob[p][a][0] = Deslocglob[(grau_lib_esf[p][a][0]-1)][0];
         }

        for(int a = 0 ; a <6; a ++) {
            Deslbarloc[p][a][0] = 0.0;
            for (int c = 0 ; c <6; c ++) {
                Deslbarloc[p][a][0] += MatrizTransf[p][a][c] * Deslbarglob[p][c][0];
            }
        }
}

// ------------------------------------------------------------------------------------------------------------------------------------------
//REAÇÕES
float reacoes_barra_loc [50][10][5];
float reacoes_barra_glob [50][10][5];
float reacoes [50][80][5];
float reacao [80][5];
float reacaoapoio[80][5];

for (int p = 0; p < barras; p++){
        for (int a = 0; a < 6; a++){
            reacoes_barra_loc[p][a][0] = 0.0;
        }

        for(int a = 0 ; a <6; a ++) {
            for (int c = 0 ; c <6; c ++) {
                reacoes_barra_loc[p][a][0] += Rigidez_artic[p][a][c] * Deslbarloc[p][c][0];
            }
            reacoes_barra_loc[p][a][0] += (esf_barra_local_carga[p][a][0]);
        }
        for(int a = 0 ; a <6; a ++) {
            reacoes_barra_glob[p][a][0] = 0.0;
            for (int c = 0 ; c <6; c ++) {
                reacoes_barra_glob[p][a][0] += MatrizTransfTranspost[p][a][c] * reacoes_barra_loc[p][c][0];
            }
        }
}

for(int p = 0; p < barras; p++){
    for(int a = 0; a < grau_lib_total;a++){
        reacoes[p][a][0] = 0.0;
    }
    for(int a = 0; a < 6;a++){
            reacoes[p][(grau_lib_esf[p][a][0])-1][0] = reacoes_barra_glob[p][a][0];
        }
}

for(int a = 0; a < grau_lib_total;a++){
    for(int p = 0; p < barras;p++){
        reacao[a][0] += reacoes[p][a][0];
    }
}

//-----------------------------------------------------------------------------------------------------------------------------------------

    //DESENVOLVIMENTO DOS RELATÓRIOS DOS RESULTADOS

    CreateDirectory("Resultados",NULL);

    // Arquivo como os valores da matriz de rigidez para cada barra no referencial local

    FILE *riglocal = fopen("Resultados/3_rigidezlocal_semrotacao.txt","w");

    fprintf(riglocal,"Matriz de rigidez local das barras no referencial local");
    fprintf(riglocal,"\n\n");

    for (int p = 0; p < barras; p++){
        fprintf(riglocal,"Barra %d \n",p+1);
        for(int a = 0; a < 6; a++){
            for(int b = 0; b < 6; b++){
                fprintf(riglocal,"%f \t",Rigidezlocal_sem_rot[p][a][b]);
            }
            fprintf(riglocal,"\n");
        }
       fprintf(riglocal,"\n\n");
    }

    fclose(riglocal);

    // Arquivo como os valores da matriz de rigidez para cada barra no referencial local (Articulações)
    FILE *riglocalart = fopen("Resultados/4_rigidezlocal_articulacao.txt","w");

    fprintf(riglocalart,"Matriz de rigidez local das barras no referencial local (Articulações)");
    fprintf(riglocalart,"\n\n");

    for (int p = 0; p < barras; p++){
        fprintf(riglocalart,"Barra %d \n",p+1);
        for(int a = 0; a < 6; a++){
            for(int b = 0; b < 6; b++){
                fprintf(riglocalart,"%f \t",Rigidez_artic[p][a][b]);
            }
            fprintf(riglocalart,"\n");
        }
       fprintf(riglocalart,"\n\n");
    }

    fclose(riglocalart);

    // Arquivo como as matrizes de transformação e suas transpostas
    FILE *rigtransf = fopen("Resultados/5_Transformacoes.txt","w");

    fprintf(rigtransf,"Matriz das Transformacoes");
    fprintf(rigtransf,"\n\n");

    for (int p = 0; p < barras; p++){
        fprintf(rigtransf,"Barra %d \n",p+1);
        for(int a = 0; a < 6; a++){
            for(int b = 0; b < 6; b++){
                fprintf(rigtransf,"%f \t",MatrizTransf[p][a][b]);
            }
            fprintf(rigtransf,"\n");
        }
       fprintf(rigtransf,"\n\n");
    }

    fprintf(rigtransf,"Matriz transposta das Transformacoes ");
    fprintf(rigtransf,"\n\n");

    for (int p = 0; p < barras; p++){
        fprintf(rigtransf,"Barra %d \n",p+1);
        for(int a = 0; a < 6; a++){
            for(int b = 0; b < 6; b++){
                fprintf(rigtransf,"%f \t",MatrizTransfTranspost[p][a][b]);
            }
            fprintf(rigtransf,"\n");
        }
       fprintf(rigtransf,"\n\n");
    }
    fclose(rigtransf);

    //Multiplicação intermediaria entre a transposta da transformacao e a matriz de rigidez no ref.local
    FILE *rigint = fopen("Resultados/6_Transf(T)_RigidezLocal.txt","w");

    fprintf(rigint,"Multiplicação intermediaria entre a transposta da transformacao e a matriz de rigidez no ref.local");
    fprintf(rigint,"\n\n");

    for (int p = 0; p < barras; p++){
        fprintf(rigint,"Barra %d \n",p+1);
        for(int a = 0; a < 6; a++){
            for(int b = 0; b < 6; b++){
                fprintf(rigint,"%f \t",mult[p][a][b]);
            }
            fprintf(rigint,"\n");
        }
       fprintf(rigint,"\n\n");
    }

    //Matriz de rigidez das barras no referencia global
    FILE *rigbarra = fopen("Resultados/7_Rigidez_barra.txt","w");

    fprintf(rigbarra,"Matriz de rigidez das barras no referencial global");
    fprintf(rigbarra,"\n\n");

    for (int p = 0; p < barras; p++){
        fprintf(rigbarra,"Barra %d \n",p+1);
        for(int a = 0; a < 6; a++){
            for(int b = 0; b < 6; b++){
                fprintf(rigbarra,"%f \t",Rigidezbarra[p][a][b]);
            }
            fprintf(rigbarra,"\n");
        }
       fprintf(rigbarra,"\n\n");
    }

    //Mapeamento
    FILE *mapa = fopen("Resultados/8_Mapeamento.txt","w");

    fprintf(mapa,"Mapeamento dos graus de liberdade da estrutura");
    fprintf(mapa,"\n\n");

    for (int p = 0; p < barras; p++){
        fprintf(mapa,"Barra %d \n",p+1);
        fprintf(mapa,"Local       Global \n");
        for(int a = 0; a < 6; a++){
            for(int b = 0; b < 2; b++){
                fprintf(mapa,"%d \t\t",mapeamento[p][a][b]);
            }
            fprintf(mapa,"\n");
        }
       fprintf(mapa,"\n\n");
    }

    //Matriz de rigidez para cada barra com as dimensões de todos os graus de liberdade
    FILE *rigbarglo = fopen("Resultados/9_Mat_rig_barra_glob.txt","w");

    fprintf(rigbarglo,"Matriz de rigidez para cada barra com as dimensões de todos os graus de liberdade");
    fprintf(rigbarglo,"\n\n");

    for (int p = 0; p < barras; p++){
        fprintf(rigbarglo,"Barra %d \n",p+1);
        for (int a = 0; a < grau_lib_total; a++){
                for(int b = 0; b < grau_lib_total; b++){
                        fprintf(rigbarglo,"%f\t",Rigidez[p][a][b]);
            }
            fprintf(rigbarglo,"\n");
        }
       fprintf(rigbarglo,"\n\n");
    }

    //Matriz de rigidez da ESTRUTURA
    FILE *rigest = fopen("Resultados/10_Mat_rig_estrutura.txt","w");

    fprintf(rigest,"Matriz de rigidez da estrutura com as dimensões de todos os graus de liberdade");
    fprintf(rigest,"\n\n");

    for (int a = 0; a < grau_lib_total; a++){
            for(int b = 0; b < grau_lib_total; b++){
                    fprintf(rigest,"%f \t",RigidezEstrutura[a][b]);
            }
            fprintf(rigest,"\n");
        }

    //Matriz de rigidez Efetiva
    FILE *rigeft = fopen("Resultados/11_Mat_rig_efetiva.txt","w");

    fprintf(rigeft,"Matriz de rigidez efetiva da estrutura para os graus de liberdade livres");
    fprintf(rigeft,"\n\n");

    for (int a = 0; a < livre; a++){
            for(int b = 0; b < livre; b++){
                    fprintf(rigeft,"%f \t",RigidezEfetiva[a][b]);
            }
            fprintf(rigeft,"\n");
        }


    //Matriz dos esforços locais aplicados aos nos da modelo (para cada barra)
    FILE *esfbarloc = fopen("Resultados/12_Esfor_nos_barras_local.txt","w");

    fprintf(esfbarloc,"Vetor dos esforços aplicados aos nos referente a cada barra");
    fprintf(esfbarloc,"\n\n");

    for (int p = 0; p < barras; p++){
        fprintf(esfbarloc,"Barra %d \n",p+1);
        fprintf(esfbarloc,"Esforços Locais        Grau de lib (GLOBAL) \n");
        for (int a = 0; a < 6; a++){
                    fprintf(esfbarloc,"%f   \t \t    %d\n ",esf_barra_local_no[p][a][0],grau_lib_esf[p][a][0]);
            }
            fprintf(esfbarloc,"\n\n");
    }

    //Matriz dos esforços locais aplicados nas barras da modelo
    FILE *esfbarloccarg = fopen("Resultados/13_Esfor_barras_local.txt","w");

    fprintf(esfbarloccarg,"Vetor dos esforços aplicados nas barras no referencial local");
    fprintf(esfbarloccarg,"\n\n");

    for (int p = 0; p < barras; p++){
        fprintf(esfbarloccarg,"Barra %d \n",p+1);
        fprintf(esfbarloccarg,"Esforços Locais (cargas)        Grau de lib (GLOBAL) \n");
        for (int a = 0; a < 6; a++){
                    fprintf(esfbarloccarg,"%f   \t \t \t      %d\n ",esf_barra_local_carga[p][a][0],grau_lib_esf[p][a][0]);
            }
            fprintf(esfbarloccarg,"\n\n");
    }

    //Matriz dos esforços locais aplicados nas barras da modelo (REFERENCIAL GLOBAL)
    FILE *esfbarglobcarg = fopen("Resultados/14_Esfor_barras_global.txt","w");

    fprintf(esfbarglobcarg,"Vetor dos esforços aplicados nas barras no referencial Global");
    fprintf(esfbarglobcarg,"\n\n");

    for (int p = 0; p < barras; p++){
        fprintf(esfbarglobcarg,"Barra %d \n",p+1);
        fprintf(esfbarglobcarg,"Esforços [Global] (cargas)        Grau de lib (GLOBAL) \n");
        for (int a = 0; a < 6; a++){
                    fprintf(esfbarglobcarg,"%f   \t \t \t      %d\n ",esf_barra_global_carga[p][a][0],grau_lib_esf[p][a][0]);
            }
            fprintf(esfbarglobcarg,"\n\n");
    }

    //Matriz dos esforços aplicados aos nos da estrutura do modelo (REFERENCIAL GLOBAL)
    FILE *esfestrutglobnos = fopen("Resultados/15_Esfor_nos_estrut.txt","w");

    fprintf(esfestrutglobnos,"Vetor dos esforços aplicados ao nos da estrutura na referencial global");
    fprintf(esfestrutglobnos,"\n\n");

    fprintf(esfestrutglobnos,"Esforços [Global] (nos) \n");
        for (int a = 0; a < grau_lib_total; a++){
                    fprintf(esfestrutglobnos,"%f \n",EsforcoNoTotal[a][0]);
            }

    //Matriz dos esforços aplicados as barras da estrutura do modelo (REFERENCIAL GLOBAL)
    FILE *esfestrutglobcarg = fopen("Resultados/16_Esfor_barras_estrut.txt","w");

    fprintf(esfestrutglobcarg,"Vetor dos esforços aplicados nas barras no referencial Global");
    fprintf(esfestrutglobcarg,"\n\n");

    fprintf(esfestrutglobcarg,"Esforços [Global]\n");
        for (int a = 0; a < grau_lib_total; a++){
                    fprintf(esfestrutglobcarg,"%f \n",EsforcoCargaTotal[a][0]);
            }

    //Matriz dos esforços totais (Nó - Carga) (REFERENCIAL GLOBAL)
    FILE *esfestrut = fopen("Resultados/17_Esfor_estrut.txt","w");

    fprintf(esfestrut,"Vetor dos esforços Totais (Nó - Cargas)");
    fprintf(esfestrut,"\n\n");

    fprintf(esfestrut,"Esforços [Totais] \n");
        for (int a = 0; a < grau_lib_total; a++){
                    fprintf(esfestrut,"%f \n",EsforcoExterno[a][0]);
            }


    //Matriz dos Deslocamentos (Nos livres)
    FILE *deslgeral = fopen("Resultados/18_Desloc_Geral.txt","w");

    fprintf(deslgeral,"Deslocamento geral");
    fprintf(deslgeral,"\n\n");

        for (int a = 0; a < livre; a++){
                    fprintf(deslgeral,"%f \n",desl[a]);
            }

    //Matriz dos Deslocamentos (Nos livres) (REFERENCIAL GLOBAL) [Graus de liberdade]
    FILE *deslgeralgrau = fopen("Resultados/19_Desloc_Geral_Grau_de_liberdade.txt","w");

    fprintf(deslgeralgrau,"Deslocamento geral (Grau de liberdade)");
    fprintf(deslgeralgrau,"\n\n");
    fprintf(deslgeralgrau,"Deslocamento              Grau de lib. (GLOBAL)\n");

        for (int a = 0; a < grau_lib_total; a++){
                    fprintf(deslgeralgrau,"%f   \t\t        %d\n",Deslocglob[a][0],a+1);
            }

    //Matriz dos Deslocamentos (Barras) (REFERENCIAL Global/Local)
    FILE *deslgeralbarra = fopen("Resultados/20_Desloc_Geral_Barra.txt","w");

    fprintf(deslgeralbarra,"Deslocamento geral (Barra)");
    fprintf(deslgeralbarra,"\n\n");

    for(int p = 0; p < barras; p++){
            fprintf(deslgeralbarra,"Barra %d \n",p+1);
            fprintf(deslgeralbarra,"GLOBAL         LOCAL \n");
        for (int a = 0; a < 6; a++){
                    fprintf(deslgeralbarra,"%f         %f \n",Deslbarglob[p][a][0],Deslbarloc[p][a][0]);
            }
        fprintf(deslgeralbarra,"\n\n");
        }

    //Matriz das reações locais (Barras) (REFERENCIAL Global/Local)
    FILE *reacaobarraloc = fopen("Resultados/21_Reacao_Barra_local.txt","w");

    fprintf(reacaobarraloc,"Reação locais para barra\n");
    fprintf(reacaobarraloc,"\n\n");

    for(int p = 0; p < barras; p++){
        fprintf(reacaobarraloc,"Barra %d \n",p+1);
        fprintf(reacaobarraloc,"Esforco aplicado            Grau de lib. Global\n");
        for (int a = 0; a < 6; a++){
                    fprintf(reacaobarraloc,"%f   \t\t\t    %d\n",reacoes_barra_loc[p][a][0],grau_lib_esf[p][a][0]);
            }
        fprintf(reacaobarraloc,"\n\n");
        }

    //Matriz das reações gloabais (Barras) (REFERENCIAL Global/Local)
    FILE *reacaobarraglob = fopen("Resultados/22_Reacao_Barra_global.txt","w");

    fprintf(reacaobarraglob,"Reação globais para barra \n");
    fprintf(reacaobarraglob,"\n\n");

    for(int p = 0; p < barras; p++){
        fprintf(reacaobarraglob,"Barra %d \n",p+1);
        fprintf(reacaobarraglob,"Esforco aplicado           Grau de lib. Global\n");
        for (int a = 0; a < 6; a++){
                    fprintf(reacaobarraglob,"%f  \t\t\t    %d\n",reacoes_barra_glob[p][a][0],grau_lib_esf[p][a][0]);
            }
        fprintf(reacaobarraglob,"\n\n");
        }

    //Matriz das reações TOTAIS
    FILE *reacaoestrut = fopen("Resultados/23_Reacao_Grau_de_liberdade.txt","w");

    fprintf(reacaoestrut,"Reação globais para a estrutura \n");
    fprintf(reacaoestrut,"\n\n");

    fprintf(reacaoestrut,"Esforco aplicado           Grau de lib. Global\n");
    for (int a = 0; a < grau_lib_total; a++){
                    fprintf(reacaoestrut,"%f  \t\t\t    %d\n",reacao[a][0],a+1);
            }

    }

