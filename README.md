# 📦 Sistema de Controle de Estoque em C

Sistema de controle de estoque desenvolvido em linguagem C, com o objetivo de praticar lógica de programação, estruturas de dados, funções e manipulação de arquivos.

O projeto permite gerenciar produtos por meio de um menu interativo no terminal, realizando operações de cadastro, consulta, atualização e remoção.

## 🚀 Funcionalidades

- Cadastrar produtos com código, nome, preço e quantidade.
- Listar todos os produtos cadastrados.
- Buscar produtos pelo código.
- Atualizar quantidades disponíveis no estoque.
- Registrar vendas e descontar as unidades vendidas.
- Remover produtos cadastrados.
- Gerar relatórios com quantidade de produtos, unidades disponíveis e valor total do estoque.
- Identificar produtos com estoque baixo.
- Salvar e recuperar automaticamente os produtos utilizando arquivo binário.

## 🛠️ Tecnologias utilizadas

- Linguagem C
- GCC (compilador)
- Visual Studio Code
- Git e GitHub

## 📚 Conceitos aplicados

- Estruturas de dados com `struct`
- Vetores
- Funções
- Estruturas condicionais (`if`, `else` e `switch`)
- Estruturas de repetição (`for`, `while` e `do while`)
- Manipulação de arquivos com `fopen`, `fread` e `fwrite`
- Entrada e saída de dados
- Organização e modularização do código

## 💻 Como executar

**1. Clone o repositório:**

```bash
git clone https://github.com/MicaelySantos/controle-estoque-c.git
```

**2. Acesse a pasta do projeto:**

```bash
cd controle-estoque-c
```

**3. Compile o programa utilizando GCC:**

```bash
gcc main.c -o estoque.exe
```

**4. Execute no Windows:**

```powershell
.\estoque.exe
```

É necessário ter o compilador GCC instalado. Em outros sistemas operacionais, o nome do executável e o comando de execução podem ser diferentes.

## 📋 Exemplo do menu

```text
================================
   SISTEMA DE CONTROLE DE ESTOQUE
================================
1 - Cadastrar produto
2 - Listar produtos
3 - Buscar produto por codigo
4 - Atualizar estoque
5 - Registrar venda
6 - Remover produto
7 - Relatorio de estoque
0 - Sair
================================
Escolha uma opcao:
```

## 💾 Armazenamento de dados

Os produtos são armazenados localmente no arquivo binário `produtos.dat`, gerado automaticamente durante a utilização do programa.

Dessa forma, os produtos cadastrados permanecem disponíveis mesmo após o encerramento do sistema.

## 🔮 Possíveis melhorias futuras

- Histórico de vendas.
- Edição de preços e nomes dos produtos.
- Relatórios de faturamento.
- Exportação de relatórios para CSV.
- Melhorias na validação das entradas.

## 👩‍💻 Desenvolvedora

**Micaely Bárbara Santos**

Estudante de Engenharia de Computação na Universidade Federal de Ouro Preto (UFOP).

Projeto desenvolvido para fins de aprendizado e aprimoramento das habilidades em programação.

**GitHub:** [MicaelySantos](https://github.com/MicaelySantos)
