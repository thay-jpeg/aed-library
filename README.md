<img src="./cabecalho.png"
style="width:5.36111in;height:1.12489in" />

**\#** **Sistema** **de** **Gerenciamento** **da** **Biblioteca**

Trata-se de um sistema para o gerenciamento de uma biblioteca,
permitindo o cadastro de livros, usuários e o controle de empréstimos e
devoluções. O sistema foi implementado na linguagem C e utiliza arquivos
binários para armazenar os dados de forma persistente, garantindo que as
informações não sejam perdidas ao fechar o programa.

**\##** **Funcionalidades** **Implementadas**

O sistema possui 10 (dez) opções, sendo:

> **1.** **Cadastrar** **livro:**
>
> a\. Esta opção permite adicionar um novo livro ao acervo da
> biblioteca.
>
> b\. **Como** **usar:** você precisará fornecer as respectivas
> credenciais do livro, como o código, título da obra, nome do autor,
> editora, o número da edição, ano de publicação e a quantidade de
> exemplares disponíveis.
>
> **2.** **Informações** **de** **um** **respectivo** **livro:**
>
> a\. Esta opção permite consultar as informações detalhadas de um livro
> registrado no sistema de acordo com seu código cadastrado.
>
> b\. **Como** **usar:** você precisará fornecer o código do livro
> exatamente como foi registrado no sistema no momento de seu cadastro,
> sem zeros à esquerda. Caso o livro existir, o sistema exibirá as
> informações. Caso contrário, uma mensagem de *‘‘não* *encontrado’’*
> será exibida.
>
> **3.** **Listar** **todos** **os** **livros** **cadastrados:**
>
> a\. Exibe uma lista formatada com as informações principais de todos
> os livros que estão no sistema, em ordem de cadastro (do antigo para o
> mais novo), com código, título da obra, nome do autor e quantidade de
> exemplares disponíveis. Caso não possuir nenhum livro no sistema, uma
> mensagem de *“nenhum* *livro* *foi* *cadastrado”* será exibida.
>
> b\. **Como** **usar:** apenas selecione a opção no menu para
> visualizar a tabela completa.
>
> **4.** **Busca** **por** **Título:**
>
> a\. Esta opção permite consultar as informações detalhadas de um livro
> registrado no sistema de acordo com o título da obra cadastrado.
>
> b\. **Como** **usar:** você precisará fornecer o nome do título do
> livro exatamente como foi registrado no sistema no momento de seu
> cadastro, com todas as letras maiúsculas ou minúsculas e espaçamentos,
> se existir. Caso o livro for encontrado, o sistema exibirá as
> informações. Caso contrário, uma mensagem de *‘‘não* *encontrado’’*
> será exibida.
>
> **5.** **Calcular** **total** **de** **livros** **cadastrados:**
>
> a\. Exibe na tela a quantidade total de livros cadastrados no sistema.
> Caso nenhum livro for cadastrado, aparecerá um resultante equivalente
> à *“0”*.
>
> b\. **Como** **usar:** apenas selecione a opção no menu para
> visualizar a quantidade total.
>
> **6.** **Cadastrar** **usuário:**
>
> a\. Esta opção registra uma nova pessoa como usuária da biblioteca.
>
> b\. **Como** **usar:** você precisará fornecer as respectivas
> credenciais da nova pessoa, como um código único e seu nome.
>
> **7.** **Empréstimo** **de** **livro:**
>
> a\. Esta opção permite realizar um empréstimo de livro a um respectivo
> usuário. A data definida para empréstimo é definida no dia atual do
> registro.
>
> b\. **Como** **usar:** você precisará informar os dados do empréstimo,
> como o código do usuário e o código do livro. Caso não houver uma
> quantidade de exemplares disponíveis para empréstimo, não será
> possível fazê-lo, exibindo uma mensagem do tipo *“não* *há*
> *quantidade* *disponível* *para* *empréstimo”*. É permitido apenas um
> empréstimo de cada livro do acervo para um usuário. Caso você tentar
> pegar emprestado mais de uma vez o mesmo livro, aparecerá uma mensagem
> “*usuário* *já* *possui* *empréstimo* *para* *este* *livro*”. Se o
> livro ou o usuário que quiser registrar o empréstimo não estiver
> cadastrado no sistema, será exibido uma mensagem *“não* *encontrado”*.
>
> **8.** **Devolução** **de** **livro:**
>
> a\. Esta opção permite realizar uma devolução de um livro emprestado a
> um respectivo usuário. A data definida para devolução é definida no
> dia atual do registro.
>
> b\. **Como** **usar:** você precisará informar os dados para a
> devolução, como o código do usuário e o código do livro emprestado.
> Caso não houver um empréstimo registrado para o respectivo usuário,
> não será possível fazê-lo, exibindo uma mensagem do tipo *“não*
> *existe* *um* *empréstimo* *para* *tal* *usuário*
>
> *deste* *livro”*. É permitido apenas uma devolução de cada livro do
> acervo para um usuário. Caso você tentar devolver mais de uma vez o
> mesmo livro, aparecerá uma mensagem “*usuário* *não* *possui*
> *empréstimo* *para* *tal* *livro*”. Se o livro ou o usuário que quiser
> registrar a devolução não estiver cadastrado no sistema, será exibido
> uma mensagem *“não* *encontrado”*.
>
> **9.** **Listar** **todos** **os** **livros** **emprestados:**
>
> a\. Exibe uma lista formatada com as informações principais de todos
> os empréstimos de livros não devolvidos que estão no sistema, em ordem
> de cadastro (do mais novo ao mais antigo), com código e nome do
> usuário, código e título da obra e data de empréstimo. Caso não
> possuir nenhum empréstimo cadastrado no sistema, uma mensagem de
> *“nenhum* *empréstimo* *registrado”* será exibida. Se você realizar a
> devolução de um empréstimo, caso for consultar a lista de todos os
> livros emprestados novamente, verá que o seu registro foi retirado
> desta tabela.
>
> b\. **Como** **usar:** apenas selecione a opção no menu para
> visualizar a tabela completa.
>
> **10.** **Carregar** **arquivo** **em** **Lote:**
>
> a\. Esta funcionalidade realiza inclusões em lote, carregando
> informações de livro, usuários e empréstimos que estão armazenados
> dentro de um arquivo de texto *.txt*. O sistema lê os dados deste
> arquivo e os insere diretamente nos arquivos binários de cadastrodo
> sistema, ideal para popular obancode forma rápida. Ele também realiza
> a contagem da quantidade de registros processados e os exibe na tela.
> O sistema também verifica a possibilidade de empréstimo de um
> respectivo livro para um usuário e exibe se foi possível realizá-lo
> com sucesso. Caso contrário, dependendo de qual for a circunstância da
> ausência de algum dado necessário para registro, exibirá mensagens
> como *“não* *encontrado”*, *“usuário* *já* *possui* *empréstimo*
> *para* *este* *livro”*, *“não* *há* *quantidade* *disponível* *para*
> *empréstimo”* e se for um empréstimo com data de devolução, informará
> que é um *“registro* *histórico”* e armazenará no arquivo binário.
> Caso houver uma opção que não seja L, U ou E no arquivo texto, uma
> mensagem *“linha* *com* *tipo* *de* *registro* *desconhecido”* será
> exibida.
>
> **b.** **Como** **usar:** você precisará informar o nome do arquivo
> texto exatamente como está registrado, com letras maiúsculas,
> minúsculas ou *underline* (\_), se existir, para o sistema puder
> acessá-lo. **Obs:** O nome do arquivo texto deve ter, no máximo, 255
> caracteres.
>
> **0.** **Sair:**
>
> a\. Sai do sistema e salva os dados do programa.
>
> b\. **Como** **usar:** apenas selecione a opção do menu.
