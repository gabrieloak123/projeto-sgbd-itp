# Projeto de SGBD em C
Projeto da disciplina de Introdução às Técnicas de Programação que visa criar um Sistema Gerencial de Banco de Dados usando C.

## Funcionalidades
* Criação de tabelas
* Listagem das tabelas criadas
* Adicionar nova linha em tabela
* Listagem de dados de uma tabela
* Pesquisar valor em uma tabela

## Sintaxe
Basicamente uma adaptação do MySQL

### Criar tabela
É possível criar tabela através do `createtable`, na qual o padrão de inserção de atributos é `type name`, nos quais os tipos são os primitivos de C:
* int
* float
* double
* char
* string

O número máximo de colunas de cada tipo é n. E ao acabar de listar os atributos desejados dê um `stop` para finalizar a criação da tabela, e em seguida declare o nome da coluna que será a chave primária.

Exemplo de entrada:
```
createtable table_name
int attribute_1
float attribute_2
double attribute_3
char attribute_4
string attribute_5
stop
pk: attribute_1
```
***
### Listar tabelas
Todas as tabelas serão listadas ao executar o comando `showtables`

Exemplo de entrada:
```
showtables
```
Exemplo de saída:
```
table_1
table_2
table_3
```
***
### Adicionar dados
Ao adicionar dados em uma determinada tabela deve-se usar o `insertinto`, após isso será retornado os atributos da tabela com seu respectivo tipo e habilitada a entrada de dados.
```
insertinto table_name
int attrb_1 | char attrb_2 | double attrb_3
value_1
value_2
value_3
```
***
### Listar dados
```
selectallfrom table_name
```
***
### Pesquisar dados
Filtros de busca: `>`, `<`, `>=`, `<=`, `=`, `~=`
```
searchin table_name
col_to_search
>
18122005
```
***
### Apagar linha
O `deletefrom` apaga uma linha específica de uma tabela, para isso é preciso que seja informada uma chave primária na linha abaixo.

Exemplo de entrada:
```
deletefrom table_name
wherepk pk_id
```
***
### Apagar tabela
Para apagar uma tabela use o `droptable`.

Exemplo de entrada:
```
droptable table_name
```
