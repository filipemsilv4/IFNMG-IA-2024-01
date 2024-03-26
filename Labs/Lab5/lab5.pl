% Fatos representando o número secreto (pode ser alterado conforme necessário)
numero_secreto(7).

% Fatos representando os números possíveis
possivel_numero(1).
possivel_numero(2).
possivel_numero(3).
possivel_numero(4).
possivel_numero(5).
possivel_numero(6).
possivel_numero(7).
possivel_numero(8).
possivel_numero(9).
possivel_numero(10).

% Regra para verificar se o palpite está correto
adivinhe(Numero) :-
    numero_secreto(Secreto),
    Numero == Secreto,
    write('Parabéns! Você adivinhou o número secreto.'), nl.

% Regras para dar dicas se o palpite estiver errado
adivinhe(Numero) :-
    numero_secreto(Secreto),
    Numero < Secreto,
    write('O número secreto é maior.'), nl,
    falha.

adivinhe(Numero) :-
    numero_secreto(Secreto),
    Numero > Secreto,
    write('O número secreto é menor.'), nl,
    falha.

% Contador de tentativas
:- dynamic tentativas/1.
tentativas(0).

% Regra para incrementar o contador de tentativas
falha :-
    tentativas(T),
    T1 is T + 1,
    retract(tentativas(T)),
    assert(tentativas(T1)),
    write('Tentativas: '), write(T1), nl.

% Menu principal
menu :-
    write('Jogo de Adivinhação'), nl,
    write('Adivinhe o número secreto entre 1 e 10'), nl,
    loop_principal.

% Loop principal
loop_principal :-
    repeat,
    write('Digite seu palpite: '),
    read(Numero),
    (   possivel_numero(Numero) ->
        adivinhe(Numero);
        write('Número inválido. Tente novamente.'), nl,
        falha
    ),
    numero_secreto(Secreto),
    Numero == Secreto,
    !.

% Iniciar o jogo
iniciar :-
    retractall(tentativas(_)), % Reseta o contador de tentativas
    assert(tentativas(0)),
    menu.
