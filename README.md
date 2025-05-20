# 📚 Sistema de Biblioteca

## 👥 Componentes do Grupo

- Gabriel Cavalcante Velasquez
- Thaynara Nascimento de Jesus

-----

## 🛠 Funcionalidades Implementadas

### 1. Cadastro de Livros (`/livros/cadastrar`)  
**O que faz:**  
Permite adicionar novos livros ao sistema com:  
- Código único (inteiro)  
- Título (até 100 caracteres)  
- Autor (até 50 caracteres)  
- Editora (até 50 caracteres)
- Edição (inteiro)
- Ano (inteiro)
- Exemplares (inteiro)

**Como usar:**  
```bash
1. Selecione "Cadastrar Livro" no menu.
2. Insira os dados solicitados.
...

*Como Executar:

#Compilar
gcc -o biblioteca main.c bibliotec.c bibliotec.h

#Executar
./biblioteca

*Notas Adicionais:

As datas devem seguir o formato DD/MM/AAAA.
Códigos de livros devem ser únicos.