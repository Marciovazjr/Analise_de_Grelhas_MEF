# Análise de Grelhas (MEF)
Programa desenvolvido na linguagem C durante a graduação de Engenharia Civil como Trabalho de conclusão de curso. 

> Título do trabalho: "**_Formulação matricial e implementação computacional para análise de grelhas_**"
 
<p align="justify"> O trabalho deve por objetivo desenvolver uma implementação computacional baseado na formulação matricial do método dos deslocamentos, capaz de descrever o comportamento das barras de grelha, determinando as reações em seus apoios, os esforços internos e os deslocamentos livres em suas extremidades, quando estas são submetidas a diferentes tipos de carregamentos. </p>

### Mas, o que é uma modelo de grelhas?

<img align = "left" src="https://user-images.githubusercontent.com/93450598/158017826-e9f21ef1-a996-40ac-9d45-8f317a874fa1.png" height = "160">

<p align="justify"> Modelo estrutural em barras retas ou curvas, situadas em um mesmo plano, sob ações externas solicitadas na direção transversal deste plano, de modo a desenvolverem em cada secção: o momento fletor (M), o esforço cortante (V) e o momento de torção (T) (SORIANO, 2005). </p>

<br/>
<br/>
 
### Fluxograma do algoritmo

<img src = "https://user-images.githubusercontent.com/93450598/158020388-535ce92e-09f4-4924-b196-174a87f3c0bc.png" height = "560">

### Implementação computacional

Modelo de Grelha | Modelo no algoritmo
:-: | :-:
![Modelo de Grelha](https://user-images.githubusercontent.com/93450598/158030850-8f7fe733-5022-4087-a8e8-362e654da5aa.png?h=100&w=200)|![Modelo no algoritmo](https://user-images.githubusercontent.com/93450598/158030906-dbb846ff-7e7c-48b7-9bae-0bfac9f49cb4.png?h=100&w=120)

### Exemplos modelados

[Exemplo 1](https://github.com/Marciovazjr/Analise_de_Grelhas_MEF/blob/main/ModelosGrelhas_txt/Exemplo1.txt) | [Exemplo 2](https://github.com/Marciovazjr/Analise_de_Grelhas_MEF/blob/main/ModelosGrelhas_txt/Exemplo2.txt)| Exemplo 3
:-: | :-: | :-:
<img src = "https://user-images.githubusercontent.com/93450598/158031333-c61d608a-dca3-4123-857c-e525aeacc4da.png" height = "200">| <img src = "https://user-images.githubusercontent.com/93450598/158032974-aa15c275-11a9-459f-be49-7657393438e8.png" height = "200"> | <img src = "https://user-images.githubusercontent.com/93450598/158031350-c671b765-71fb-48c5-96bd-3c7050c65d04.png" height = "200">
Exemplo 4 | Exemplo 5 | Exemplo 6
<img src = "https://user-images.githubusercontent.com/93450598/158031371-967faa09-27a9-4962-be3c-5021dd141cd5.png" height = "200">| <img src = "https://user-images.githubusercontent.com/93450598/158033068-dce81bce-8848-4e01-be65-5c3c5f7416ff.png" height = "200">| <img src = "https://user-images.githubusercontent.com/93450598/158033093-77748ba3-4194-4b67-95de-70d710ef2659.png" height = "200">
Exemplo 7 | Exemplo 8 
<img src = "https://user-images.githubusercontent.com/93450598/158033133-2b031514-336a-47e5-be86-d85e8c3c7270.png" height = "200">| <img src = "https://user-images.githubusercontent.com/93450598/158033153-690773dc-ee08-4206-887b-07763856cbab.png" height = "200">

### Modelos com vinculações/articulações

Entre as barras | Nos apoios do arranjo
:-: | :-: 
<img src = "https://user-images.githubusercontent.com/93450598/158033301-bfa755c6-134a-4133-88f9-b116e6eb39a4.png" height = "250">| <img src = "https://user-images.githubusercontent.com/93450598/158033313-3f774138-ee03-4c83-8575-6d9774e1ee1c.png" height = "250">

### Referenciais

> KASSIMALI, Aslam. Grid. In: KASSIMALI, Aslam. Matrix Analysis of Structures. Carbondale: Cengace Learning, 2011. p. 433-455.

> SORIANO, Humberto Lima. Analise de estrutura: Formulação matricial e implementação computacional. Rio de Janeiro: Ciência Moderna, 2005.


