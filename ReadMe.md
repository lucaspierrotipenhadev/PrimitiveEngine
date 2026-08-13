Bem vindo a documentação do primitive engine! Vou te ajudar a ler a ordem correta da documentação, para ajudar a compreender melhor o sistema.

Caso for apenas usar o sistema, recomendo seguir o passo 1.
Caso for aprender sobre o sistema, recomendo seguir o passo 2.


--------------------------------------------------------------------------------------------------------------------------------------------
1. Leitura para quem quer apenas usar o sistema

1.1 Leia o arquivo docs/PublicAPI.md para aprender como utilizar o sistema.
--------------------------------------------------------------------------------------------------------------------------------------------


--------------------------------------------------------------------------------------------------------------------------------------------
2. Leitura para quem quer aprender e implementar o sistema

2.1.  Leia primeiro o arquivo  docs/Arcuitecture.md.
    Nele estará a visão geral do projeto.

2.2.  Leia em segundo o arquivo docs/ClassArcuitecture.md.
    Nele estará a arquitetura de todas as classes do sistema.

2.3.  Leia em terceiro o arquivo docs/LifeTime.md
    Nele estará o ciclo de vida da aplicação.

2.4.  Leia em quarto o arquivo docs/Diagram.md
    Nele estará o diagram simplificado do sistema.

2.5.  Leia em quinto o arquivo docs/ownership.md
    Este arquivo é importante para saber como evitar bugs, já que ele explica quem cria quem, e quem destrói quem.

2.6.  Leia em sexto o arquivo docs/DomainDriverDesign.md.
    Nele estará descrito os serviços, objetos de domínio, recursos, objetos de infraestrutura, interfaces, backend, objetos matemático e objetos gráficos do sistema.

2.7.  Leia o arquivo docs/CodingGuidelines.md para entender a padronização de códigos do projetos.
--------------------------------------------------------------------------------------------------------------------------------------------

Para compilar e rodar o sistema user:

Para compilar: & "C:\Program Files\CMake\bin\cmake.exe" -S . -B build

Para rodar: & "C:\Program Files\CMake\bin\cmake.exe" --build build

Para refazer o build: Remove-Item -Recurse -Force build/