Contexto: A engine precisa ser multiplataforma e abstrair criação de janelas, entrada e áudio.

Decisão: Utilizar SDL3 como camada de plataforma.

Consequências: Reduzimos código específico de cada sistema operacional e mantemos a possibilidade de trocar apenas a implementação da camada de plataforma no futuro.