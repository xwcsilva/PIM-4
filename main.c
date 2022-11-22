#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "tipos.h"

t_usuario  *usuarios  = NULL;
t_paciente *pacientes = NULL;
int         n_pacientes = 0, n_usuarios = 0;
char        linha[102];

FILE *arq_usuarios;
FILE *arq_pacientes;
FILE *arq_relatorio;

int le_usuarios () {
    int i,j;

    arq_usuarios = fopen("usuarios","r");
    if (arq_usuarios == NULL)
        return (-1);

    i = fread(&n_usuarios,sizeof(int),1,arq_usuarios);
    if (i > 0) {
        usuarios = malloc(sizeof(t_usuario) * n_usuarios);
        if (usuarios == NULL)
            return (-1);
        i = fread(usuarios,sizeof(t_usuario),n_usuarios,arq_usuarios);
        j = fclose(arq_usuarios);
        return (i + j);
    }
}

int salva_usuarios() {
    int i,j ;

    arq_usuarios = fopen("usuarios","w");
    if (arq_usuarios == NULL)
        return (-1);

    i = fwrite(&n_usuarios,sizeof(int),1,arq_usuarios);
    i = fwrite(usuarios,sizeof(t_usuario),n_usuarios,arq_usuarios);
    j = fclose(arq_usuarios);
    return (i + j);
}

int calc_idade(n) {
    t_data dn,dd;
    int id;

    dn = pacientes[n].dt_nasc;
    dd = pacientes[n].dt_diag;
    id = atoi(dd.ano) - atoi(dn.ano);
    if (atoi(dd.dia) >= atoi(dn.dia) && atoi(dd.mes) >= atoi(dn.mes))
        return(id);
    else
        return(id - 1);
}

int salva_pacientes () {
    int i,j ;

    arq_pacientes = fopen("pacientes","w");
    if (arq_pacientes == NULL)
        return (-1);

    i = fwrite(&n_pacientes,sizeof(int),1,arq_pacientes);
    i = fwrite(pacientes,sizeof(t_paciente),n_pacientes,arq_pacientes);
    j = fclose(arq_pacientes);
    return (i + j);
}

int le_pacientes () {
    int i,j;

    arq_pacientes = fopen("pacientes","r");
    if (arq_pacientes == NULL)
        return (-1);

    i = fread(&n_pacientes,sizeof(int),1,arq_pacientes);
    if (i > 0) {
        pacientes = malloc(sizeof(t_paciente) * n_pacientes);
        if (pacientes == NULL)
            return (-1);
        i = fread(pacientes,sizeof(t_paciente),n_pacientes,arq_pacientes);
        j = fclose(arq_pacientes);
        return (i + j);
    }
}

int gera_relatorio () {
    int i,j,idade;
    char *n_relat = "relatorio.txt";

    arq_relatorio = fopen(n_relat,"w");
    if (arq_relatorio == NULL)
        return (-1);
    for (i = 0; i < n_pacientes; i++) {
        //if (strlen(pacientes[i].comorbidades) > 0) {
        idade = calc_idade(i);
        if (idade > 65)
            fprintf(arq_relatorio,"CEP: %s, idade: %d\n",pacientes[i].endereco.cep, idade);
    }
    j = fclose(arq_relatorio);
    printf("Gerado o relatorio no arquivo %s.\n",n_relat);
    return (j);
}

void le_linha() {
    char c;
    int  n;

    fgets(linha,100,stdin);
    for (n = 0; n < 102; n++)
        if (linha[n] == '\n')
            linha[n] = 0;
}

void obtem_dados_paciente(n) {
    printf ("Nome : ");
    le_linha(); strcpy(pacientes[n].nome,linha);
    printf ("Telefone (somente numeros) : ");
    le_linha(); strcpy(pacientes[n].telefone,linha);
    printf ("CPF (somente numeros) : ");
    le_linha(); strcpy(pacientes[n].cpf,linha);
    printf ("Data de nascimento (DD MM AAAA) : ");
    le_linha(); sscanf(linha,"%s %s %s", &pacientes[n].dt_nasc.dia, &pacientes[n].dt_nasc.mes, &pacientes[n].dt_nasc.ano);
    printf ("Data do diagnostico : ");
    le_linha(); sscanf(linha,"%s %s %s", &pacientes[n].dt_diag.dia, &pacientes[n].dt_diag.mes, &pacientes[n].dt_diag.ano);
    printf ("Email : ");
    le_linha(); strcpy(pacientes[n].email,linha);
    printf ("Rua : ");
    le_linha(); strcpy(pacientes[n].endereco.rua,linha);
    printf ("Numero : ");
    le_linha(); strcpy(pacientes[n].endereco.num,linha);
    printf ("Bairro : ");
    le_linha(); strcpy(pacientes[n].endereco.bairro,linha);
    printf ("Cidade : ");
    le_linha(); strcpy(pacientes[n].endereco.cidade,linha);
    printf ("Estado : ");
    le_linha(); strcpy(pacientes[n].endereco.estado,linha);
    printf ("CEP : ");
    le_linha(); strcpy(pacientes[n].endereco.cep,linha);
    printf ("Comorbidades : ");
    le_linha(); strcpy(pacientes[n].comorbidades,linha);
    printf("\n\nObrigado!\n\n");
}

void novo_paciente() {
    int n = n_pacientes;

    printf("Favor informar os seguintes dados do paciente:\n");

    pacientes = realloc(pacientes,sizeof(t_paciente) * (n+1));

    obtem_dados_paciente(n);

    n_pacientes++;
}

void edita_paciente () {
    int n;

    if (n_pacientes == 0) {
        printf("Nao ha pacientes para editar.\n");
        return;
    }
    printf ("Digite o numero do paciente que deseja editar os dados (0 - %d)\n",n_pacientes-1);
    le_linha();
    if (valida_n_pacientes(n = atoi(linha)) < 0)
        return;
    printf("Informe novamente os dados do paciente %d (%s):\n",n,pacientes[n].nome);
    obtem_dados_paciente(n);
}

int valida_n_pacientes(int n) {
    if (n < 0 || n > n_pacientes - 1) {
        printf("O numero do paciente deve estar entre 0 e %d\n",n_pacientes-1);
        return -1;
    }
    return 0;
}

void apaga_um_paciente () {
    int i,n;

    if (n_pacientes == 0) {
        printf("Nao ha pacientes para apagar\n");
        return;
    }
    if (n_pacientes == 1) {
        printf ("Apagando o unico paciente, %s\n",pacientes[0].nome);
        free(pacientes);
        n_pacientes = 0;
        return;
    }
    printf ("Lista de pacientes : \n");
    for (i = 0; i < n_pacientes; i++)
        printf("Nome do paciente %s, numero: %d\n", pacientes[i].nome,i);
    printf("Qual deles deseja apagar ? ");
    le_linha(); n = atoi(linha);
    if (valida_n_pacientes(n) < 0)
        return;
    i = n;
    do {
        memcpy(&pacientes[i],&pacientes[i+1],sizeof(t_paciente));
        i++;
    } while (i < n_pacientes - 1);
    n_pacientes--;
    pacientes = realloc(pacientes,sizeof(t_paciente) * (n_pacientes));
}

void mostra_dados () {
    int i,n;

    if (n_pacientes == 0) {
        printf("Nao ha pacientes para mostrar\n");
        return;
    }
    printf("Escolha: T para todos ou digite o numero de um paciente (0 - %d):\n",n_pacientes-1);
    le_linha();

    if (linha[0] == 'T' || linha[0] == 't') {
        i = 0; n = n_pacientes;
    } else {
        n = atoi(linha);
        if (valida_n_pacientes(n) < 0)
            return;
        i = n;
    }
    do {
        printf ("Paciente %d\n",i);
        printf ("\nNome: %s\n", pacientes[i].nome);
        printf ("Telefone: %s\n", pacientes[i].telefone);
        printf ("CPF: %s\n", pacientes[i].cpf);
        printf ("Data Nascimento: %s/%s/%s\n",  pacientes[i].dt_nasc.dia,
                                                pacientes[i].dt_nasc.mes,
                                                pacientes[i].dt_nasc.ano);
        printf ("Data Diagnostico: %s/%s/%s\n", pacientes[i].dt_diag.dia,
                                                pacientes[i].dt_diag.mes,
                                                pacientes[i].dt_diag.ano);
        printf ("Idade (na data do dignostico): %d\n",calc_idade(i));
        printf ("Email: %s\n", pacientes[i].email);
        printf ("Rua: %s\n", pacientes[i].endereco.rua);
        printf ("Numero: %s\n", pacientes[i].endereco.num);
        printf ("Bairro: %s\n", pacientes[i].endereco.bairro);
        printf ("Cidade: %s\n", pacientes[i].endereco.cidade);
        printf ("Estado: %s\n", pacientes[i].endereco.estado);
        printf ("CEP: %s\n", pacientes[i].endereco.cep);
        printf ("Comorbidades: %s ",pacientes[i].comorbidades);
        printf ("\n\n");
        i++;
    } while (i < n);
}

char *menu() {
    printf("\n\nMenu\n\n");
    printf("(0) Fim\n\n");
    printf("(1) Adiciona um paciente\n");
    printf("(2) Apaga um paciente\n");
    printf("(3) Edita os dados de um paciente\n");
    printf("(4) Mostra dados dos pacientes\n");
    printf("(5) Gera arquivo com os dados para a Secretaria de Saude\n");
    printf("(6) Adiciona um usuario\n");
    printf("Escolha: ");
    le_linha();
    return(linha);
}

void adiciona_usuario () {
    n_usuarios++;
    usuarios = realloc(usuarios,sizeof(t_usuario) * (n_usuarios));
    printf("Nome do usuário:\n");
    le_linha(); strcpy(usuarios[n_usuarios-1].nome,linha);
    printf("Senha do usuário:\n");
    le_linha(); strcpy(usuarios[n_usuarios-1].senha,linha);
}

int valida_login() {
    char nome[21],senha[21];
    int i;

    if (le_usuarios() == -1) { // Não existem usuarios cadastrados no sistema
        printf("Nao ha usuarios no sistema, vamos criar um:\n");
        adiciona_usuario();
    } else {
        printf("Nome do usuario do sistema:\n");
        le_linha(); strcpy(nome,linha);
        printf("Senha do usuario do sistema:\n");
        le_linha(); strcpy(senha,linha);
        for (i = 0; i < n_usuarios; i++)
            if(strcmp(nome,usuarios[i].nome) == 0 && strcmp(senha,usuarios[i].senha) == 0)
                return 0;
        return -1;
    }
}


int main() {
    int i;

    if (valida_login() < 0) {
        printf ("Erro no usuario ou senha, tente novamente, finalizando...\n");
        exit(-1);
    }

    le_pacientes();

    while (1) {
        i = atoi(menu());
        printf("Comando escolhido: %d\n",i);
        if (i == 0) {
            printf("Terminando...\n");
            break;
        }
        switch (i) {
            case 1: novo_paciente(); break;
            case 2: apaga_um_paciente(); break;
            case 3: edita_paciente(); break;
            case 4: mostra_dados(); break;
            case 5: gera_relatorio(); break;
            case 6: adiciona_usuario(); break;
            default: printf("Digite um comando valido.\n"); break;
        }
    }
    gera_relatorio();
    salva_pacientes();
    salva_usuarios();
    free(pacientes);
}
