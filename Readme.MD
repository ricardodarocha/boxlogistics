# Sobre

Falar sobre a empresa e o que ela faz

## Time

Membros do time e funções

|nome|funcao|
|-|-|
|COD|Ricardo|

COD Cheif of Department
DEV Senior Developer 

## Features do sistema

// todos os cadastros sao listas duplamente encadeada, permitindo navegar pra frente e pra tras  
// apenas cadastros auxiliares sao listas simplesmente encadeadas, porque tem poucos registros e nao tem necessidade de paginacao  
// a visualizacao de listas possui suporte a paginacao, permitindo visualizar poucos registros por vez  
// a ordenacao de entregas por data de entrega é colocada em arvore para permitir ordenacao  
// cada entrega gera qrcode para colocar na embalagem do produto, garantindo o carregamento correto  

## Principais funcionalidades

O módulo principal do sistema está disponível para todos os clientes e visam controlar todas as etapas de um sistema de logística
Desde a recepção e estoque de materiais  
Até o despacho de pedidos  
Controlando a rota, o status de cada entrega

O sistema possui relatórios que permite
- Gerenciar o risco das entregas  
- Etiquetar cada entrega de acordo com a carga  
- Agendar entregas e retiradas de produtos (devolução)  

Alguns recursos avançados do sistema incluem

- Seguros  
- Etiquetas e Certificações   
- Logística Reversa  
- Controle de Cargas Perigosas  



## Requisitos

//      produtos -> lista duplamente encadeada  
//      veiculos -> tipo (caminhao) porte placa motorista origem(propria, terceiro) km(kilometragem)  
//      doca -> Um objeto representa uma doca, contem numero e endereco, se esta ocupada ou nao, e um semaforo, que indica se a doca esta liberada ou nao  
//      fila -> fila de caminhoes,  
//      esteira -> fila de pedidos prontos para carregar   
//      empilhamento -> empilhamento permite saber a ordem exata que as cargas serão inseridas no caminhão  
//      clientes -> permite armazenar por longa data o historico de dados do cliente, mudanças de endereco, etc   
//      entregas -> esta struct permite guardar os dados da entrega   

//     CRUD     (produto, veiculos, entregas, cargas)  
//     inserir  
//     navegar (proximo, anterior)  
//     buscar  
//     listar(pagina)  
