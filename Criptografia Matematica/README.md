# Projeto de Criptografia Matemática

**Disciplina:** Algoritmo e Pensamento Computacional  
**Professor:** Francisco de Assis Cavallaro  
**Linguagem:** C

## 1. Objetivo

Desenvolver um programa em linguagem C que utilize criptografia simples e sequências matemáticas para codificar e recuperar palavras.

## 2. Funcionamento

O programa permite escolher entre criptografar, descriptografar e sair. O usuário informa uma palavra de até 15 letras, um valor de SHIFT entre 0 e 25 e uma sequência matemática.

A criptografia utiliza duas camadas:
- **Camada 1:** deslocamento das letras baseado na cifra de César.
- **Camada 2:** deslocamento adicional baseado nos termos de uma sequência numérica.

## 3. Sequências disponíveis

- **PA:** progressão aritmética, com termos 1, 2, 3, 4...
- **PG:** progressão geométrica, com termos 1, 2, 4, 8...
- **Fibonacci:** sequência 1, 1, 2, 3, 5, 8...
- **Números primos:** sequência 2, 3, 5, 7, 11...

## 4. Arquivos e registro

O programa grava as operações realizadas no arquivo `resultado_criptografia.txt`, registrando a palavra codificada ou recuperada, o SHIFT, o tipo de sequência e a quantidade de letras.

## 5. Como executar

Compile o programa no terminal MSYS2 UCRT64:

```bash
gcc main.c -o main.exe
```

Execute com:

```bash
./main.exe
```

## 6. Conceitos aplicados

O projeto utiliza variáveis, funções, estruturas condicionais, laços de repetição, vetores de caracteres, operações matemáticas, menus e manipulação de arquivos com `fopen`, `fprintf` e `fclose`.

## 7. Limitações

Este programa é um exercício acadêmico de criptografia. A cifra utilizada é simples e não deve ser considerada segura para proteger informações reais.
