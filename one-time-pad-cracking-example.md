<h1>EXEMPLO DE QUEBRA DE CRIPTOGRAFIA - ONE-TIME PAD</h1>

Observe três textos cifrados, todos resultantes da criptografia de textos simples ASCII contendo apenas letras e espaços em inglês, usando o one-time pad e a mesma chave. O décimo byte do primeiro texto cifrado é 0xA8, o décimo byte do segundo texto cifrado é 0xED e o décimo byte do terceiro texto cifrado é 0xBD.

<b>Qual é o décimo caractere ASCII do terceiro texto simples?</b>

- "a"
- "p"
- space (caracter de espaço)
- não é possível identificar

Analisando os valores hexadecimais dos textos cifrados + as possibilidades de resultados acima, podemos concluir que a CHAVE para gera esses resultados usando XOR é:

    chave: 1?0? 110?

Pois:

    0xBD  - 1011 1101
    
        X O R
    
    space - 0010 0000
    "a"   - 0110 0001
    "p"   - 0111 0000

Nos dando 3 opções de CHAVE que alocam os valores da chave que estão escondidos para encontrar o valor em 0xBD:

    A) - space (caracter de espaço)
    0010 0000 -> XOR 0xBD -> CHAVE A: 1001 1101

    B) - a
    0110 0001 -> XOR 0xBD -> CHAVE B: 1101 1100

    C) - p
    0111 0000 -> XOR 0xBD -> CHAVE C: 1100 1100

Usando CADA CHAVE GERADA em cada valor hexadecimal dos textos cifrados temos:

    0xA8 -> [
        CHAVE A -> 0011 0101 -> "#" (X) <-- texto incorreto
        CHAVE B -> 0111 0100 -> "t"
        CHAVE C -> 0110 0101 -> "e"
    ]

    0xED -> [
        CHAVE A -> 0111 0000 -> "p"
        CHAVE B -> 0010 0001 -> "!" (X) <-- texto incorreto
        CHAVE C -> 0010 0000 -> space
    ]

    0xBD -> [
        CHAVE A -> 0010 0000 -> space
        CHAVE B -> 0110 0001 -> "a"
        CHAVE C -> 0111 0000 -> "p"
    ]

Logo a CHAVE A e a CHAVE B não podem estar corretas pois ambas geram caracteres diferentes de "textos simples" conforme o enunciado:

> "[...] resultantes da criptografia de textos simples ASCII <b>contendo apenas letras e espaços</b> em inglês [...]"

Por tanto a única chave possível é a CHAVE C. Logo, o resultado da questão é:

- "p"

Pois:

    0xBD -> (usando CHAVE C) -> 0111 0000 -> 70 -> "p"


---------------------

<h1>Conclusão</h1>

O exemplo acima mostra a fragilidade de ONE-TIME PAD quando as mensagens criptográficas são geradas pela mesma chave porque podemos comparar caracteres das mesmas posições de mensagens anteriores eliminando chaves que não funcionaram.

Claro que o exemplo anterior tem um facilitador pois ele deixa como opção alguns caracteres a serem testados. Porém isso é indiferente sob o ponto de vista técnico, porque é bem simples criar um algorítimo para gerar multiplas chaves para todos os caracteres e testá-los automaticamente, eliminado os que não passam pelos testes.