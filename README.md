# CPPChat

Sistema de mensagens em tempo real desenvolvido em C++20 utilizando arquitetura cliente-servidor, comunicação TCP, multithreading e persistência de dados.

🚧 Em desenvolvimento
Versão atual: 0.1.0

## Objetivo

O objetivo deste projeto é estudar e demonstrar conceitos avançados de desenvolvimento de sistemas utilizando C++, incluindo:

* Programação de redes com sockets TCP
* Concorrência e multithreading
* Sincronização de recursos compartilhados
* Arquitetura cliente-servidor
* Persistência de dados
* Protocolos de comunicação
* Boas práticas de engenharia de software

---

## Principais Funcionalidades

### Autenticação

* Cadastro de usuários
* Login
* Logout

### Salas de Conversa

* Criação de salas
* Entrada em salas
* Saída de salas
* Listagem de salas

### Mensagens

* Envio de mensagens em tempo real
* Broadcast para participantes da sala
* Histórico persistente de mensagens

### Administração

* Lista de usuários conectados
* Registro de logs
* Monitoramento de conexões

---

## Arquitetura

```text
+-----------+
| Cliente A |
+-----------+
      |
+-----------+
| Cliente B |
+-----------+
      |
      | TCP
      |
      ▼
+----------------------+
|      Chat Server     |
+----------------------+
| Authentication       |
| Room Manager         |
| User Manager         |
| Message Service      |
| Persistence Layer    |
+----------------------+
      |
      ▼
+----------------------+
|       SQLite         |
+----------------------+
```

---

## Tecnologias

| Tecnologia  | Finalidade                |
| ----------- | ------------------------- |
| C++20       | Linguagem principal       |
| TCP Sockets | Comunicação em rede       |
| Threads     | Processamento concorrente |
| SQLite      | Persistência de dados     |
| JSON        | Protocolo de mensagens    |
| CMake       | Build do projeto          |
| Google Test | Testes automatizados      |

---

## Estrutura do Projeto

```text
cpp-chat/
│
├── client/
│
├── server/
│
├── common/
│
├── protocol/
│
├── database/
│
├── tests/
│
├── docs/
│
└── CMakeLists.txt
```

---

## Modelo de Concorrência

A versão inicial utiliza o modelo:

1 conexão = 1 thread

```text
Main Thread
     │
     ├── Client Thread 1
     ├── Client Thread 2
     ├── Client Thread 3
     └── Client Thread N
```

O objetivo é explorar:

* std::thread
* std::mutex
* std::lock_guard
* sincronização de recursos compartilhados

Versões futuras poderão utilizar Thread Pool e I/O assíncrona.

---

## Protocolo de Comunicação

Exemplo de login:

```json
{
  "type": "login",
  "username": "ana",
  "password": "123456"
}
```

Exemplo de envio de mensagem:

```json
{
  "type": "chat_message",
  "room": "geral",
  "content": "Olá pessoal"
}
```

---

## Roadmap

### Fase 1

* [ ] Servidor TCP
* [ ] Cliente TCP
* [ ] Conexão simultânea de múltiplos clientes

### Fase 2

* [ ] Cadastro de usuários
* [ ] Login
* [ ] Logout

### Fase 3

* [ ] Salas de conversa
* [ ] Broadcast de mensagens
* [ ] Usuários online

### Fase 4

* [ ] Persistência com SQLite
* [ ] Histórico de mensagens
* [ ] Logs

### Fase 5

* [ ] Testes automatizados
* [ ] Refatoração
* [ ] Documentação final

---

## Decisões Arquiteturais

As principais decisões de arquitetura estão documentadas em:

```text
docs/architecture.md
```

Incluindo:

* Cliente-Servidor vs Peer-to-Peer
* TCP vs UDP
* SQLite vs PostgreSQL
* JSON vs Protocolo Binário
* Estratégia de Concorrência
* Modelo de Persistência

---

## Objetivos de Aprendizado

Este projeto foi desenvolvido para aprofundar conhecimentos em:

* Programação de Sistemas
* Redes de Computadores
* Concorrência
* Arquitetura de Software
* C++ Moderno

---

## Licença

Projeto desenvolvido para fins educacionais e de portfólio.
