# Projeto de SGBD em C
Projeto da disciplina de Introdução às Técnicas de Programação que visa criar um Sistema Gerencial de Banco de Dados usando C.

## Prereqs
Projeto compatível com linux, necessário CMake para rodar

Ubuntu/Debian:
```
sudo apt-get install cmake
```

Execute o `run.sh`, crie a pasta txts e execute a main
```
./run.sh
chmod +x run.sh
cd build
mkdir txts
./main
```

## Menu
Ao iniciar o programa será aberto um menu com as seguintes opções:
```
===========================================
Digite o número correspondente à operação:
0. Sair
1. Criar tabela
2. Listar tabelas
3. Adicionar dados
4. Listar dados
5. Pesquisar dados
6. Apagar linha
7. Apagar tabela
===========================================
```
### 0.Sair
O programa é encerrado

### 1.Criar tabela
Digite o nome da tabela e em seguida os atributos, o padrão de inserção de atributos é `type name`, nos quais os tipos são os primitivos de C:
* int
* float
* double
* char
* string

O número máximo de colunas de cada tipo é n. E ao acabar de listar os atributos desejados dê um `stop` para finalizar a criação da tabela, e em seguida declare o nome da coluna que será a chave primária

Exemplo de entrada:
```
table_paciente
int cpf
float altura
char tipo_sanguineo
string nome
stop
Digite qual dos atributos será a Chave Primária:
(Repetirá até digitar um dos argumentos acima)
cpf
```
***
### 2.Listar tabelas
Todas as tabelas criadas serão listadas ao selecionar a opção

Exemplo de saída:
```
table_1
table_2
table_3
```
***
### 3.Adicionar dados
Após selecionar a opção serão e declarar a tabela desejada, serão retornados os atributos da tabela com seu respectivo tipo e habilitada a entrada de dados

Exemplo de entrada:
```
Digite o nome da tabela:
TimesSerieA
Tabela: TimesSerieA
id             nome           mundiais       rebaixamentos  
------------------------------------------------------------
1              SaoPaulo       3              0              
2              Palmeiras      0              2              
=========================================

```
***
### 4.Listar dados
Será imprimido todo o conteúdo da tabela desejada

Exemplo de entrada:
```
Digite o nome da tabela:
TimesSerieA
Tabela: TimesSerieA
id             nome           mundiais       rebaixamentos  
------------------------------------------------------------
1              SaoPaulo       3              0              
2              Palmeiras      0              2              
=========================================
```
***
### 5.Apagar linha
Apaga uma linha específica de uma tabela, para isso é preciso que seja informada uma chave primária na linha abaixo

Exemplo de entrada:
```
Digite a tabela que deseja deletar dados:
TimesSerieA
Tabela: TimesSerieA
id             nome           mundiais       rebaixamentos  
------------------------------------------------------------
1              SaoPaulo       3              0              
4              Santos         1              1              
Digite a Chave Primária referente à linha que será deletada:
4
```
***
### 6.Apagar tabela
Exclui a tabela digitada da lista de tabelas, cuidado
Exemplo de entrada:
```
TimesSerieA
TimesJaRebaixados

Digite a tabela que deseja deletar:
TimesSerieA
Tem certeza que deseja deletar a tabela TimesSerieA? (S/N)
S
Tabela deletada

```
