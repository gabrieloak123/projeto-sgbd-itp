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

### Listar tabelas
```
showtables
```
### Adicionar dados
```
insertinto table_name
attrb_1 
attrb_2
attrb_3
```

### Listar dados
```
selectallfrom table_name
```

### Pesquisar dados
Filtros de busca: `>`, `<`, `>=`, `<=`, `=`, `~=`
```
searchin table_name
col_to_search
>
18122005
```

### Apagar linha
```
deletefrom table_name
wherepk pk_id
```

### Apagar tabela
```
droptable table_name
```
