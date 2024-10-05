#include <iostream>
#include <string>
#include <cstring>

using namespace std;

typedef struct contato {
    contato() {
        ant = NULL;
        prox = NULL;
        email = "";
    }
    string nome;
    string sobrenome;
    string nomeCompleto;
    string numTel;
    string email;
    contato *prox;
    contato *ant;
} Contato;

int novoContatoOrdenado(Contato **lista, string nome, string sobrenome, string numTel) {
    Contato *novo = new Contato;
    if (novo == NULL) return 0;

    novo->nome = nome;
    novo->sobrenome = sobrenome;
    novo->nomeCompleto = novo->nome + " " + novo->sobrenome;
    novo->numTel = numTel;


    if (*lista == NULL || (*lista)->nomeCompleto > novo->nomeCompleto) {
        novo->prox = *lista;
        if (*lista != NULL)
            (*lista)->ant = novo;
        *lista = novo;
    } else {
        Contato *aux = *lista;
        while (aux->prox && aux->prox->nomeCompleto < novo->nomeCompleto)
            aux = aux->prox;

        novo->prox = aux->prox;
        novo->ant = aux;
        if (aux->prox) 
            aux->prox->ant = novo;
        aux->prox = novo;
    } 
    return 1;
}

int busca(Contato **lista, string nomeCompleto) {
    if (*lista == NULL) return 0;
    Contato *aux = *lista;
    while (aux->prox && aux->nomeCompleto != nomeCompleto) {
        aux = aux->prox;
    }
    if (aux->nomeCompleto == nomeCompleto) return 1;
    return 0;
}

int removerContato(Contato **lista, string nomeCompleto) {
    if (busca(lista, nomeCompleto) == 0) return 0;

    if ((*lista)->prox == NULL) {
        delete *lista;
        *lista = NULL;
    } else {
        Contato *aux = *lista;
        while (aux->prox && aux->nomeCompleto != nomeCompleto)
            aux = aux->prox;

        if (aux->prox == NULL) {
            aux->ant->prox = NULL;
        } else if (aux->ant == NULL) {
            *lista = (*lista)->prox;
            (*lista)->ant = NULL;
        } else {
            aux->ant->prox = aux->prox;
            aux->prox->ant = aux->ant;
        }
        delete aux;    
    }
    return 1;
}

void mostrarLista(Contato *lista) {
    system("clear");
    cout << "\t CONTATOS\n" << endl;
    if (lista == NULL) {
        cout << "\tLista vazia\n" << endl;
        return;
    }

    Contato *aux = lista;
    int i = 0;
    while (aux) {
        cout << ++i << ".[" + aux->nomeCompleto << "]" << endl;
        aux = aux->prox;
    }
    cout << "\n\tFim da lista\n" << endl;
}

int menuEditarInfo(Contato *aux) {
    system("clear");
    cout << "\t" << aux->nomeCompleto << "\n" << endl;
    cout << "Nome: " << aux->nome << endl;
    cout << "Sobrenome: " << aux->sobrenome << endl;
    cout << "Numero: " << aux->numTel << endl;
    cout << "E-mail: " << aux->email << endl;
    cout << endl;

    int opc = 0;
    cout << "[1] - Adicionar/Editar E-mail." << endl;
    cout << "[2] - Editar numero." << endl;
    cout << "[0] - Voltar." << endl;
    cout << "\nEscolha uma opcao: ";
    cin >> opc;
    cout << endl;
    return opc;
}

void editarInfo(Contato *aux) {
    while (true) {
        switch (menuEditarInfo(aux)) {
            case 0:
                return;
            case 1:
                cout << "Digite o endereco de E-mail: ";
                cin >> aux->email;
                break;
            case 2:
                cout << "Digite o novo numero (Sem espacos): ";
                cin >> aux->numTel;
                break;
            default:
                cout << "Opcao invalida.";
                getchar();
                break;
        }
    }
}

int menuAbrirContato(Contato *aux) {
    system("clear");
    cout << "\t" << aux->nomeCompleto << "\n" << endl;
    cout << "Nome: " << aux->nome << endl;
    cout << "Sobrenome: " << aux->sobrenome << endl;
    cout << "Numero: " << aux->numTel << endl;
    cout << "E-mail: " << aux->email << endl;
    cout << endl;

    int opc = 0;
    cout << "[1] - Editar informacoes." << endl;
    cout << "[0] - Voltar." << endl;
    cout << "\nEscolha uma opcao: ";
    cin >> opc;
    cout << endl;
    return opc;
}

void abrirContato(Contato **lista, string nomeCompleto) {
    Contato *aux = *lista;
    while (aux->nomeCompleto != nomeCompleto) aux = aux->prox;

    while (true) {
        switch (menuAbrirContato(aux)) {
            case 0:
                return;
            case 1:
                editarInfo(aux);
                break;
            default:
                cout << "Opcao invalida.";             
                getchar();
                break;
        }
    }
    return;
}

int menuPrincipal(Contato *lista) {
    int opc = 0;
    system("clear");
    mostrarLista(lista);
    cout << "[1] - Adicionar novo contato." << endl;
    cout << "[2] - Remover contato." << endl;
    cout << "[3] - Abrir contato." << endl;
    cout << "[0] - Sair." << endl;
    cout << "\nEscolha uma opcao: ";
    cin >> opc;
    cout << endl;
    return opc;
}

int main() {
    Contato *lista = NULL;
    string nome, sobrenome, numTel, nomeCompleto;
    char SN = 'N';

    while (true) {
        switch (menuPrincipal(lista)) {
            case 0:
                cout << "Deseja mesmo sair? [s/n] ";
                cin >> SN;  

                if (SN == 's' || SN == 'S') 
                    return 0;
                break;
            case 1:
                cout << "Primeiro nome: ";
                cin >> nome;
                cout << "Sobrenome: ";
                cin >> sobrenome;
                cout << "Numero (Sem espacos): ";
                cin >> numTel;
                cout << endl;

                if (busca(&lista, nome + " " + sobrenome)) {
                    cout << "Contato já existente.";
                } else {
                    if (novoContatoOrdenado(&lista, nome, sobrenome, numTel)) {
                        cout << "Contato adicionado.";
                    } else {
                        cout << "Falha ao adicionar contato.";
                    }
                }
                getchar();
                break;
            case 2:
                if (lista != NULL) {
                    cout << "Qual contato deseja remover?" << endl;
                    cout << "Nome completo: ";
                    cin >> nome;
                    cin >> sobrenome;
                    cout << endl;

                    if (removerContato(&lista, nome + " " + sobrenome)) {
                        cout << "Contato removido.";
                    } else {
                        cout << "Contato nao existe.";
                    }
                } else {
                    cout << "Lista vazia.";
                }
                getchar();
                break;
            case 3:
                if (lista != NULL) {
                    cout << "Qual contato deseja abrir?" << endl;
                    cout << "Nome completo: ";
                    cin >> nome;
                    cin >> sobrenome;
                    cout << endl;

                    if (busca(&lista, nome + " " + sobrenome) == 0) {
                        getchar();
                        cout << "Contato nao existe." << endl;
                    } else {
                        abrirContato(&lista, nome + " " + sobrenome);
                    }
                } else {
                    cout << "Lista vazia.";
                    getchar();
                }
                break;
            default:
                cout << "Opcao invalida.";
                getchar();
                break;
        }
        getchar();
    }
    return 0;
}