# **Projeto Exchange de Criptomoedas 2**

## Sergio de Siqueira Santos - 22.124.082-3

Para utilizar este projeto como investidor, execute **"investidor.exe"**
Para utilizar como administrador, execute **"administrador.exe"**

O objetivo do projeto é simular uma exchange de criptomoedas. Com o crescimento do mundo das criptomoedas, é interessante simular uma transação de Bitcoin, Ethereum, Ripple, etc.

O programa foi completamente reescrito, para que aceite as novas funcionalidades do administrador. Agora é possível ter quantos usuários o administrador desejar, com um novo sistema de
armazenamento, em arquivos binários ao invés de texto. Além disso, o administrador também pode criar qualquer moeda que desejar, informando o nome, código de identificação, cotação inicial, 
taxa de compra e venda (o código de identificação é uma string de até 5 caracteres que permite que o programa faça as alterações necessárias nos dados).

Cada usuário tem seu próprio CPF, senha e nome. Para simplificar, o CPF do usuário é apenas um número - de 1 a 10 - e sua senha é o mesmo número seguido de "2345"
Por exemplo, o usuário 4 é dono da pasta "user4", seu CPF é "4" e sua senha é "42345" (devido ao limite de 2^32 de um int, vale mais a pena colocar um número menor)

O CPF do administrador é 4002, e a senha é 8922.

Como não é possível criar um fork do próprio repositório, o projeto foi feito em uma branch do projeto original. Todas as branches com o nome "PROJETO 3" são as pertinentes à este projeto.

Obrigado pela atenção!!!
