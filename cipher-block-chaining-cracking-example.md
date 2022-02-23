
<h1>Exercício:</h1>  

Um remetente criptografa uma mensagem de 8 bytes `sendme$2` (codificada em ASCII) usando criptografia CBC, resultando em texto cifrado `0xFF 09 28 30 8C 93 81 06 39 D0 81 5A 07 79 17 43`. Qual o texto cifrado irá descriptografar a mensagem para `sendme$4`

<h2>Resposta:</h2>  

Sabemos que:

    "sendme$2"
    0xFF 09 28 30 8C 93 81 06 39 D0 81 5A 07 79 17 43


Também sabemos que precisamos de apenas 1 byte da chave para alterar o valor de `2` para `4`. 

O valor `2` está posicionado no 8° byte `06`.

Analisando a cifra anterior podemos calcular o byte da chave com o texto original:

    "2" -> 0x32 -> 00110010
     ?  -> 0x06 -> 00000110
                     XOR
    key -> 0x34 -> 00110100

Agora que temos o byte da chave que altera o valor do texto podemos calcular o resultado:

    "4" -> 0x34 -> 00110100
    key -> 0x34 -> 00110100
                     XOR
    res -> 0x00 -> 00000000

Isso conclui que o texto cifrado que irá descriptografar a mensagem para `sendme$4` é:

`0xFF 09 28 30 8C 93 81 00 39 D0 81 5A 07 79 17 43`

