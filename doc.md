# CPPChat - Documento de Arquitetura (Versão 1.0)

## 1. Visão Geral

### Objetivo

Desenvolver um sistema de mensagens em tempo real baseado em arquitetura cliente-servidor utilizando C++ moderno (C++20), comunicação TCP, multithreading e persistência de dados.

O sistema permitirá que múltiplos usuários se conectem simultaneamente ao servidor, realizem autenticação, ingressem em salas de conversa e troquem mensagens em tempo real.

---

# 2. Escopo

## Incluído no projeto

* Cadastro de usuários
* Login e logout
* Múltiplos clientes simultâneos
* Salas de conversa
* Envio de mensagens públicas
* Histórico persistente de mensagens
* Consulta de usuários online
* Logs do servidor

## Fora do escopo (versão inicial)

* Interface gráfica
* Criptografia TLS
* Compartilhamento de arquivos
* Chamadas de voz
* Vídeo
* Aplicação web

---

# 3. Requisitos Funcionais

## RF-01 Cadastro de usuário

O sistema deve permitir registrar novos usuários.

Dados:

* username
* password

Resultado:

* sucesso
* usuário já existente

---

## RF-02 Login

O sistema deve autenticar usuários registrados.

Resultado:

* autenticado
* senha inválida
* usuário inexistente

---

## RF-03 Logout

O sistema deve permitir encerrar uma sessão ativa.

---

## RF-04 Criação de sala

Usuários autenticados podem criar salas.

Exemplos:

#geral
#cpp
#games

---

## RF-05 Entrada em sala

Usuário autenticado pode ingressar em uma sala existente.

---

## RF-06 Saída de sala

Usuário pode sair da sala atual.

---

## RF-07 Envio de mensagens

Usuário pode enviar mensagens para todos os participantes da sala.

---

## RF-08 Recebimento de mensagens

Todos os participantes da sala devem receber mensagens em tempo real.

---

## RF-09 Consulta de usuários online

Usuário pode listar participantes conectados.

---

## RF-10 Histórico

Usuário pode consultar mensagens anteriores de uma sala.

---

# 4. Requisitos Não Funcionais

## RNF-01 Concorrência

O servidor deve suportar múltiplos clientes simultaneamente.

---

## RNF-02 Disponibilidade

Falhas de um cliente não devem interromper o servidor.

---

## RNF-03 Escalabilidade

A arquitetura deve permitir futura migração para thread pool.

---

## RNF-04 Desempenho

Mensagens devem ser entregues com baixa latência.

---

## RNF-05 Manutenibilidade

Componentes devem possuir responsabilidades claramente separadas.

---

## RNF-06 Portabilidade

O sistema deve compilar em Linux e Windows.

---

# 5. Casos de Uso

UC-01 Registrar usuário

Ator:
Usuário

Fluxo:

1. Solicita cadastro
2. Sistema valida
3. Sistema persiste usuário
4. Sistema retorna resultado

---

UC-02 Login

Ator:
Usuário

Fluxo:

1. Envia credenciais
2. Sistema autentica
3. Sessão é criada
4. Usuário entra no sistema

---

UC-03 Participar de sala

Ator:
Usuário autenticado

Fluxo:

1. Solicita entrada
2. Servidor valida sala
3. Usuário é adicionado

---

UC-04 Enviar mensagem

Ator:
Usuário autenticado

Fluxo:

1. Usuário envia mensagem
2. Servidor registra histórico
3. Servidor distribui mensagem
4. Clientes recebem mensagem




###### MODELO DE DADOS ######



## Tabela users

id
username
password_hash
created_at

---

## Tabela rooms

id
name
created_at

---

## Tabela room_members

room_id
user_id

---

## Tabela messages

id
room_id
user_id
content
created_at

---

# Relacionamentos

User 1 ---- N Messages

Room 1 ---- N Messages

Room N ---- N Users




# Protocolo de Comunicação

## Login

Cliente -> Servidor

{
"type":"login",
"username":"ana",
"password":"123456"
}

Servidor -> Cliente

{
"type":"login_response",
"success":true
}

---

## Entrar em sala

{
"type":"join_room",
"room":"geral"
}

---

## Enviar mensagem

{
"type":"chat_message",
"room":"geral",
"content":"Olá pessoal"
}

---

## Broadcast

{
"type":"message",
"sender":"ana",
"room":"geral",
"content":"Olá pessoal",
"timestamp":"2026-05-30T14:30:00"
}

---

## Listar usuários

{
"type":"list_users"
}



Diagrama de Componentes

┌───────────────────────┐
│       Client          │
└──────────┬────────────┘
           │
           ▼
┌───────────────────────┐
│    Network Layer      │
└──────────┬────────────┘
           │
           ▼
┌───────────────────────┐
│   Message Router      │
└──────────┬────────────┘
           │
 ┌─────────┼──────────┐
 ▼         ▼          ▼
Auth    RoomMgr    MsgService
 │         │          │
 └─────────┼──────────┘
           ▼
      Database


Diagrama de Sequência — Login

Cliente
   |
   | LOGIN
   |
   ▼
Servidor
   |
   | validar usuário
   |
   ▼
Banco
   |
   | resultado
   |
   ▼
Servidor
   |
   | login_response
   |
   ▼
Cliente


Diagrama de Sequência — Envio de Mensagem

Cliente A
   |
   | chat_message
   |
   ▼
Servidor
   |
   | salva histórico
   |
   ▼
Banco

Servidor
   |
   | broadcast
   |
   ├────► Cliente B
   |
   ├────► Cliente C
   |
   └────► Cliente D


Estratégia de Concorrência

1 conexão = 1 thread

Main Thread
     |
     ├── Accept Client
     |
     ├── Thread Cliente 1
     ├── Thread Cliente 2
     ├── Thread Cliente 3
     └── Thread Cliente N



Recursos compartilhados:

UserManager
RoomManager
MessageHistory



Proteção:

std::mutex
std::lock_guard


Em versões futuras a arquitetura poderá migrar para Thread Pool e Event Loop para melhorar escalabilidade.



por que TCP, SQLite, JSON, thread por conexão e C++20.
# Decisões Arquiteturais

## Escolha do Protocolo TCP

O sistema utiliza TCP (Transmission Control Protocol) como protocolo de transporte para comunicação entre clientes e servidor.

### Motivação

Uma aplicação de chat exige que mensagens sejam entregues corretamente e na ordem em que foram enviadas. O TCP oferece:

* Entrega confiável dos dados.
* Reenvio automático de pacotes perdidos.
* Controle de fluxo.
* Garantia de ordenação das mensagens.
* Conexão persistente entre cliente e servidor.

### Alternativas Consideradas

#### UDP

O UDP possui menor sobrecarga e menor latência, porém não garante:

* entrega dos pacotes;
* ordenação;
* detecção automática de perdas.

Como a confiabilidade é mais importante que alguns milissegundos de latência para um sistema de mensagens, TCP foi considerado mais adequado.

### Possíveis Evoluções

Em versões futuras, recursos específicos poderiam utilizar UDP, como notificações de presença ou aplicações multimídia, mantendo o TCP para mensagens de texto.

---

## Escolha do SQLite

O sistema utiliza SQLite como mecanismo de persistência.

### Motivação

O objetivo da primeira versão é possuir persistência local simples, sem dependência de serviços externos.

O SQLite oferece:

* Banco de dados embarcado.
* Nenhum processo adicional em execução.
* Arquivo único de armazenamento.
* Fácil distribuição e configuração.
* Excelente integração com C++.
* Baixa complexidade operacional.

Para um sistema de chat de pequeno e médio porte, o SQLite atende plenamente os requisitos do projeto.

### Alternativas Consideradas

#### PostgreSQL

Embora ofereça maior escalabilidade e recursos avançados, exigiria:

* instalação de servidor;
* configuração adicional;
* administração de banco.

Esses fatores aumentariam a complexidade inicial sem trazer benefícios significativos para o escopo atual.

### Possíveis Evoluções

Uma camada de abstração para persistência permitirá substituir SQLite por PostgreSQL ou outro banco relacional sem impacto significativo nas regras de negócio.

---

## Escolha do Formato JSON

As mensagens trocadas entre cliente e servidor serão serializadas em JSON.

### Motivação

O JSON foi escolhido por ser:

* legível por humanos;
* fácil de depurar;
* amplamente utilizado;
* simples de integrar com diferentes linguagens.

Exemplo:

{
"type":"chat_message",
"room":"geral",
"content":"Olá pessoal"
}

Durante o desenvolvimento, a legibilidade do protocolo facilita testes, inspeção de tráfego e correção de problemas.

### Alternativas Consideradas

#### Protocolo Binário

Protocolos binários oferecem melhor desempenho e menor consumo de banda, porém aumentam significativamente a complexidade de desenvolvimento e depuração.

Como este projeto prioriza clareza arquitetural e aprendizado, JSON foi considerado a melhor escolha inicial.

### Possíveis Evoluções

O protocolo poderá migrar futuramente para formatos binários como Protocol Buffers ou MessagePack, preservando a mesma estrutura lógica das mensagens.

---

## Estratégia de Concorrência: Thread por Conexão

A primeira versão do sistema adota o modelo Thread-per-Connection.

### Motivação

Cada cliente conectado possui uma thread dedicada responsável pelo recebimento e processamento de mensagens.

Benefícios:

* Implementação simples.
* Facilidade de entendimento.
* Separação clara entre conexões.
* Excelente valor educacional para estudo de concorrência.

Estrutura:

Main Thread
├── Cliente 1
├── Cliente 2
├── Cliente 3
└── Cliente N

Essa abordagem permite explorar:

* std::thread
* std::mutex
* std::lock_guard
* sincronização de recursos compartilhados

### Limitações

O número de threads cresce proporcionalmente ao número de conexões.

Em aplicações com milhares de usuários simultâneos, essa estratégia deixa de ser eficiente.

### Possíveis Evoluções

Em versões futuras, o servidor poderá migrar para:

* Thread Pool
* Reactor Pattern
* Event Loop
* I/O Assíncrona

Essas abordagens são utilizadas em servidores de alta escalabilidade.

---

## Escolha do C++20

O projeto será desenvolvido utilizando o padrão C++20.

### Motivação

O objetivo é demonstrar conhecimento de recursos modernos da linguagem e práticas atuais de desenvolvimento.

Recursos utilizados:

* std::jthread
* std::span
* std::chrono
* ranges
* conceitos modernos de RAII
* smart pointers
* bibliotecas padrão mais robustas

### Benefícios

* Código mais seguro.
* Melhor legibilidade.
* Menor probabilidade de vazamentos de memória.
* Melhor suporte a concorrência.
* Maior aderência ao mercado atual de desenvolvimento C++.

### Justificativa do uso do c++20

A utilização de C++20 demonstra atualização tecnológica e conhecimento das práticas modernas da linguagem, substituindo abordagens legadas comuns em sistemas antigos.




Por que arquitetura cliente-servidor P2P

"Porque o objetivo do projeto é resolver descoberta de nós e consenso distribuído. Eu queria focar em redes TCP, concorrência e arquitetura de backend. Um modelo cliente-servidor me permiti estudar esses temas sem adicionar a complexidade de um sistema distribuído."

## Escolha da Arquitetura Cliente-Servidor

O sistema adota uma arquitetura cliente-servidor, na qual todos os clientes se conectam a um servidor central responsável por autenticação, gerenciamento de salas, persistência de mensagens e distribuição de eventos.

### Motivação

A arquitetura cliente-servidor foi escolhida por oferecer um modelo mais simples, seguro e adequado aos objetivos do projeto.

O servidor atua como fonte única de verdade para:

* usuários autenticados;
* salas existentes;
* histórico de mensagens;
* estado das conexões.

Essa centralização reduz a complexidade da aplicação e facilita a implementação de funcionalidades como login, controle de acesso e armazenamento persistente.

### Benefícios

#### Controle centralizado

Todas as regras de negócio ficam concentradas em um único componente.

Isso evita inconsistências entre clientes e simplifica a manutenção do sistema.

#### Persistência simplificada

O histórico de mensagens e os dados dos usuários são armazenados em um único banco de dados.

Não é necessário sincronizar informações entre diversos participantes da rede.

#### Segurança

A autenticação ocorre apenas no servidor.

Os clientes não precisam confiar uns nos outros para validar identidades ou permissões.

#### Facilidade de monitoramento

Logs, métricas e auditoria podem ser realizados em um único ponto do sistema.

### Alternativa Considerada: Peer-to-Peer (P2P)

Em uma arquitetura peer-to-peer, cada participante pode atuar simultaneamente como cliente e servidor.

Exemplo:

Usuário A <--> Usuário B

Usuário A <--> Usuário C

Usuário B <--> Usuário C

Embora essa abordagem elimine a necessidade de um servidor central, ela introduz desafios significativos:

* descoberta de participantes;
* sincronização de estado;
* resolução de conflitos;
* autenticação distribuída;
* persistência compartilhada;
* gerenciamento de conexões NAT e firewall.

Esses desafios aumentariam consideravelmente a complexidade do projeto sem agregar valor aos objetivos principais de estudo.

### Decisão

A arquitetura cliente-servidor foi considerada a solução mais adequada por permitir foco nos principais temas do projeto:

* programação de redes;
* sockets TCP;
* concorrência;
* sincronização;
* persistência de dados;
* arquitetura de software.

Além disso, esse modelo reflete a arquitetura utilizada pela maioria dos sistemas de mensagens modernos.


## Comparação de Arquiteturas

### Cliente-Servidor vs Peer-to-Peer (P2P)

| Critério                         | Cliente-Servidor       | Peer-to-Peer (P2P)       |
| -------------------------------- | ---------------------- | ------------------------ |
| Complexidade de implementação    | Baixa a média          | Alta                     |
| Curva de aprendizado             | Mais simples           | Mais complexa            |
| Gerenciamento de usuários        | Centralizado           | Distribuído              |
| Autenticação                     | Simples                | Complexa                 |
| Persistência de dados            | Centralizada           | Distribuída              |
| Histórico de mensagens           | Fácil de implementar   | Complexo de sincronizar  |
| Consistência dos dados           | Alta                   | Pode haver divergências  |
| Monitoramento e logs             | Centralizados          | Distribuídos             |
| Controle de acesso               | Simples                | Complexo                 |
| Escalabilidade horizontal        | Limitada pelo servidor | Naturalmente distribuída |
| Tolerância a falhas              | Dependente do servidor | Mais resiliente          |
| Consumo de recursos nos clientes | Baixo                  | Maior                    |
| Depuração                        | Mais simples           | Mais difícil             |
| Segurança                        | Centralizada           | Distribuída              |
| Adequação ao projeto             | Alta                   | Baixa                    |

### Vantagens da Arquitetura Cliente-Servidor

* Modelo amplamente utilizado em sistemas de mensagens modernos.
* Facilita a implementação de autenticação e autorização.
* Simplifica a persistência de dados.
* Possui menor complexidade arquitetural.
* Facilita testes, monitoramento e manutenção.
* Permite foco nos objetivos principais do projeto: redes, concorrência e sincronização.

### Desvantagens da Arquitetura Cliente-Servidor

* Possui ponto único de falha.
* O servidor pode se tornar gargalo sob alta carga.
* Exige infraestrutura dedicada para hospedagem.
* Escalabilidade depende da capacidade do servidor.

### Vantagens da Arquitetura Peer-to-Peer

* Não depende de um servidor central.
* Melhor distribuição de carga entre participantes.
* Maior tolerância à falha de nós individuais.
* Potencialmente mais escalável para grandes redes.

### Desvantagens da Arquitetura Peer-to-Peer

* Implementação significativamente mais complexa.
* Descoberta de participantes é desafiadora.
* Sincronização de estado entre nós.
* Maior dificuldade de autenticação e autorização.
* Persistência distribuída mais complexa.
* Depuração e monitoramento mais difíceis.

### Decisão Arquitetural

Para este projeto foi escolhida a arquitetura Cliente-Servidor.

A decisão foi baseada no objetivo principal do projeto: estudar programação de redes, sockets TCP, concorrência, sincronização e arquitetura de backend utilizando C++ moderno.

Embora uma solução Peer-to-Peer apresente vantagens em termos de descentralização, ela introduz problemas de sistemas distribuídos que não fazem parte do escopo desta primeira versão.



Compilar
g++ -std=c++20 src/server/main.cpp -o test.exe
.\test.exe


Build do cmake
cmake -S . -B build
cmake --build build

Execução
.\build\chat_server.exe
ou
.\build\Debug\chat_server.exe

Resultado esperado:
CPPChat Server Starting...
Waiting for connections...



