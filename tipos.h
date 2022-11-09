#ifndef TIPOS_H_INCLUDED
#define TIPOS_H_INCLUDED

typedef struct usuario {
    char nome[11];
    char senha[11];
} t_usuario;

typedef struct data {
    char dia[4], mes[4], ano[6];
} t_data;

typedef struct ende {
    char rua[31];
    char num[11];
    char bairro[16];
    char cidade[16];
    char estado[4];
    char cep[10];
} t_ende;

typedef struct paciente {
    char nome[61];
    char cpf[15];
    char telefone[13];
    t_ende endereco;
    t_data dt_nasc;
    char email[51];
    t_data dt_diag;
    char comorbidades[101];
} t_paciente;

#endif // TIPOS_H_INCLUDED
