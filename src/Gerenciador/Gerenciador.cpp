#include "Gerenciador.h"
#include <fstream>
#include <cctype> // Para formatação de caracteres (tolower)
#include <limits> // Para numeric_limits



void Gerenciador::comandos(Grafo* grafo) {
    while (true) {
        cout << endl << "--------------------------------------------------------------------------------------------------" << endl;
        cout << "Digite uma das opcoes abaixo e pressione enter:" << endl << endl;
        cout << "(a) Fecho transitivo direto de um no;" << endl;
        cout << "(b) Fecho transitivo indireto de um no;" << endl;
        cout << "(c) Caminho minimo (Dijkstra);" << endl;
        cout << "(d) Caminho minimo (Floyd);" << endl;
        cout << "(e) Arvore Geradora Minima (Algoritmo de Prim);" << endl;
        cout << "(f) Arvore Geradora Minima (Algoritmo de Kruskal);" << endl;
        cout << "(g) Arvore de caminhamento em profundidade;" << endl;
        cout << "(h) Raio, diametro, centro e periferia do grafo;" << endl;
        cout << "(0) Sair;" << endl << endl;

        char resp;
        cin >> resp;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << endl;

        switch (tolower(resp)) {
            case 'a': {
                if (!grafo->in_direcionado) {
                    cout << "ERRO: Esta funcionalidade e valida apenas para grafos direcionados." << endl;
                    break;
                }
                char id_no = get_id_entrada();
                vector<char> fecho = grafo->fecho_transitivo_direto(id_no);
                cout << "Fecho transitivo direto de " << id_no << ": ";
                imprimir_vector_char(fecho);

                if (pergunta_imprimir_arquivo("fecho_trans_dir.txt")) {
                    ofstream outfile("fecho_trans_dir.txt");
                    if (outfile.is_open()) {
                        for (size_t i = 0; i < fecho.size(); ++i) {
                            outfile << fecho[i] << (i < fecho.size() - 1 ? "," : "");
                        }
                        outfile << endl;
                        outfile.close();
                        cout << "Saida salva em fecho_trans_dir.txt" << endl;
                    } else {
                        cout << "ERRO: Nao foi possivel criar o arquivo de saida." << endl;
                    }
                }
                break;
            }

            case 'b': {
                if (!grafo->in_direcionado) {
                    cout << "ERRO: Esta funcionalidade e valida apenas para grafos direcionados." << endl;
                    break;
                }
                char id_no = get_id_entrada();
                vector<char> fecho = grafo->fecho_transitivo_indireto(id_no);
                cout << "Fecho transitivo indireto de " << id_no << ": ";
                imprimir_vector_char(fecho);

                if (pergunta_imprimir_arquivo("fecho_trans_indir.txt")) {
                    ofstream outfile("fecho_trans_indir.txt");
                    if (outfile.is_open()) {
                        for (size_t i = 0; i < fecho.size(); ++i) {
                            outfile << fecho[i] << (i < fecho.size() - 1 ? "," : "");
                        }
                        outfile << endl;
                        outfile.close();
                        cout << "Saida salva em fecho_trans_indir.txt" << endl;
                    } else {
                        cout << "ERRO: Nao foi possivel criar o arquivo de saida." << endl;
                    }
                }
                break;
            }

            case 'c': {
                if (!grafo->in_ponderado_aresta) {
                    cout << "ERRO: O algoritmo de Dijkstra requer um grafo ponderado nas arestas." << endl;
                    break;
                }
                char id_no_1 = get_id_entrada();
                char id_no_2 = get_id_entrada();
                if (grafo->getNo(id_no_1) == nullptr || grafo->getNo(id_no_2) == nullptr) {
                    cout << "ERRO: Um ou ambos os vertices nao existem no grafo." << endl;
                    break;
                }
                vector<char> caminho = grafo->caminho_minimo_dijkstra(id_no_1, id_no_2);
                cout << "Caminho minimo de " << id_no_1 << " para " << id_no_2 << " (Dijkstra): ";
                imprimir_vector_char(caminho);

                if (pergunta_imprimir_arquivo("caminho_minimo_dijkstra.txt")) {
                    ofstream outfile("caminho_minimo_dijkstra.txt");
                    if (outfile.is_open()) {
                        for (size_t i = 0; i < caminho.size(); ++i) {
                            outfile << caminho[i] << (i < caminho.size() - 1 ? "," : "");
                        }
                        outfile << endl;
                        outfile.close();
                        cout << "Saida salva em caminho_minimo_dijkstra.txt" << endl;
                    } else {
                        cout << "ERRO: Nao foi possivel criar o arquivo de saida." << endl;
                    }
                }
                break;
            }

            case 'd': {
                if (!grafo->in_ponderado_aresta) {
                    cout << "ERRO: O algoritmo de Floyd requer um grafo ponderado nas arestas." << endl;
                    break;
                }
                char id_no_1 = get_id_entrada();
                char id_no_2 = get_id_entrada();
                if (grafo->getNo(id_no_1) == nullptr || grafo->getNo(id_no_2) == nullptr) {
                    cout << "ERRO: Um ou ambos os vertices nao existem no grafo." << endl;
                    break;
                }
                vector<char> caminho = grafo->caminho_minimo_floyd(id_no_1, id_no_2);
                cout << "Caminho minimo de " << id_no_1 << " para " << id_no_2 << " (Floyd): ";
                imprimir_vector_char(caminho);

                if (pergunta_imprimir_arquivo("caminho_minimo_floyd.txt")) {
                    ofstream outfile("caminho_minimo_floyd.txt");
                    if (outfile.is_open()) {
                        for (size_t i = 0; i < caminho.size(); ++i) {
                            outfile << caminho[i] << (i < caminho.size() - 1 ? "," : "");
                        }
                        outfile << endl;
                        outfile.close();
                        cout << "Saida salva em caminho_minimo_floyd.txt" << endl;
                    } else {
                        cout << "ERRO: Nao foi possivel criar o arquivo de saida." << endl;
                    }
                }
                break;
            }

            case 'e': {
                if (grafo->in_direcionado) {
                    cout << "ERRO: O algoritmo de Prim e aplicavel apenas a grafos nao direcionados." << endl;
                    break;
                }
                if (!grafo->in_ponderado_aresta) {
                    cout << "ERRO: O algoritmo de Prim requer um grafo ponderado nas arestas." << endl;
                    break;
                }
                if (!grafo->ehConexo()) { // Verificação restaurada
                    cout << "ERRO: O grafo nao e conexo, nao e possivel gerar uma AGM." << endl;
                    break;
                }
                
                int tam;
                string mensagem = "Digite o tamanho do subconjunto (entre 2 e " + to_string(grafo->ordem) + "): ";
                tam = solicitarInteiro(mensagem, grafo->ordem);

                if (tam > 0 && tam <= grafo->ordem) {
                    vector<char> ids = get_conjunto_ids(grafo, tam);
                    Grafo* agm = grafo->arvore_geradora_minima_prim(ids);
                    cout << "Arvore Geradora Minima (Prim):" << endl;
                    imprimir_grafo(agm);

                    if (pergunta_imprimir_arquivo("agm_prim.txt")) {
                        ofstream outfile("agm_prim.txt");
                        if (outfile.is_open()) {
                            // Lógica de salvar o grafo no arquivo
                            for (No* no : agm->lista_adj) {
                                outfile << no->id << ":";
                                if (!no->arestas.empty()) {
                                    for (size_t i = 0; i < no->arestas.size(); ++i) {
                                        outfile << " " << no->arestas[i]->id_no_alvo;
                                        if (agm->in_ponderado_aresta) outfile << "(" << no->arestas[i]->peso << ")";
                                        if (i < no->arestas.size() - 1) outfile << " ->";
                                    }
                                }
                                outfile << endl;
                            }
                            outfile.close();
                            cout << "Saida salva em agm_prim.txt" << endl;
                        } else {
                            cout << "ERRO: Nao foi possivel criar o arquivo de saida." << endl;
                        }
                    }
                    delete agm;
                } else {
                    cout << "Valor invalido para o tamanho do subconjunto." << endl;
                }
                break;
            }

            case 'f': {
                if (grafo->in_direcionado) {
                    cout << "ERRO: O algoritmo de Kruskal e aplicavel apenas a grafos nao direcionados." << endl;
                    break;
                }
                if (!grafo->in_ponderado_aresta) {
                    cout << "ERRO: O algoritmo de Kruskal requer um grafo ponderado nas arestas." << endl;
                    break;
                }
                if (!grafo->ehConexo()) { // Verificação restaurada
                    cout << "ERRO: O grafo nao e conexo, nao e possivel gerar uma AGM." << endl;
                    break;
                }
                
                int tam;
                string mensagem = "Digite o tamanho do subconjunto (entre 2 e " + to_string(grafo->ordem) + "): ";
                tam = solicitarInteiro(mensagem, grafo->ordem);
                
                if (tam > 0 && tam <= grafo->ordem) {
                    vector<char> ids = get_conjunto_ids(grafo, tam);
                    Grafo* agm = grafo->arvore_geradora_minima_kruskal(ids);
                    cout << "Arvore Geradora Minima (Kruskal):" << endl;
                    imprimir_grafo(agm);

                     if (pergunta_imprimir_arquivo("agm_kruskal.txt")) {
                        ofstream outfile("agm_kruskal.txt");
                        if (outfile.is_open()) {
                            for (No* no : agm->lista_adj) {
                                outfile << no->id << ":";
                                if (!no->arestas.empty()) {
                                    for (size_t i = 0; i < no->arestas.size(); ++i) {
                                        outfile << " " << no->arestas[i]->id_no_alvo;
                                        if (agm->in_ponderado_aresta) outfile << "(" << no->arestas[i]->peso << ")";
                                        if (i < no->arestas.size() - 1) outfile << " ->";
                                    }
                                }
                                outfile << endl;
                            }
                            outfile.close();
                            cout << "Saida salva em agm_kruskal.txt" << endl;
                        } else {
                            cout << "ERRO: Nao foi possivel criar o arquivo de saida." << endl;
                        }
                    }
                    delete agm;
                } else {
                    cout << "Valor invalido para o tamanho do subconjunto." << endl;
                }
                break;
            }

            case 'g': {
                char id_no = get_id_entrada();
                if (grafo->getNo(id_no) == nullptr) {
                    cout << "ERRO: O vertice nao existe no grafo." << endl;
                    break;
                }
                Grafo* arvore = grafo->arvore_caminhamento_profundidade(id_no);
                cout << "Arvore de caminhamento em profundidade a partir de " << id_no << ":" << endl;
                imprimir_grafo(arvore);

                 if (pergunta_imprimir_arquivo("arvore_caminhamento_profundidade.txt")) {
                    ofstream outfile("arvore_caminhamento_profundidade.txt");
                    if (outfile.is_open()) {
                         for (No* no : arvore->lista_adj) {
                            outfile << no->id << ":";
                            if (!no->arestas.empty()) {
                                for (size_t i = 0; i < no->arestas.size(); ++i) {
                                    outfile << " " << no->arestas[i]->id_no_alvo;
                                    if (arvore->in_ponderado_aresta) outfile << "(" << no->arestas[i]->peso << ")";
                                    if (i < no->arestas.size() - 1) outfile << " ->";
                                }
                            }
                            outfile << endl;
                        }
                        outfile.close();
                        cout << "Saida salva em arvore_caminhamento_profundidade.txt" << endl;
                    } else {
                        cout << "ERRO: Nao foi possivel criar o arquivo de saida." << endl;
                    }
                }
                delete arvore;
                break;
            }

            case 'h': {
                if (grafo->in_direcionado) {
                    cout << "ERRO: Raio, diametro, centro e periferia sao para grafos nao direcionados." << endl;
                    break;
                }
                if (!grafo->in_ponderado_aresta) {
                    cout << "AVISO: Este calculo e mais significativo para grafos ponderados nas arestas." << endl;
                }
                int r = grafo->raio();
                int d = grafo->diametro();
                vector<char> cent = grafo->centro();
                vector<char> perif = grafo->periferia();
                imprimir_h_output(r, d, cent, perif);

                if (pergunta_imprimir_arquivo("raio_diametro_centro_periferia.txt")) {
                    ofstream outfile("raio_diametro_centro_periferia.txt");
                    if (outfile.is_open()) {
                        outfile << r << endl;
                        outfile << d << endl;
                        for (size_t i = 0; i < cent.size(); ++i) {
                            outfile << cent[i] << (i < cent.size() - 1 ? "," : "");
                        }
                        outfile << endl;
                        for (size_t i = 0; i < perif.size(); ++i) {
                            outfile << perif[i] << (i < perif.size() - 1 ? "," : "");
                        }
                        outfile << endl;
                        outfile.close();
                        cout << "Saida salva em raio_diametro_centro_periferia.txt" << endl;
                    } else {
                        cout << "ERRO: Nao foi possivel criar o arquivo de saida." << endl;
                    }
                }
                break;
            }

            case '0': {
                cout << "Encerrando o programa." << endl;
                return; // MUDANÇA 3: 'return' encerra a função e, consequentemente, o laço while.
            }
            default: {
                cout << "Opcao invalida" << endl;
                break;
            }
        }
    }
}

char Gerenciador::get_id_entrada() {
    cout << "Digite o id de um no: ";
    char id;
    cin >> id;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return id;
}

vector<char> Gerenciador::get_conjunto_ids(Grafo *grafo, int tam) {
    vector<char> ids = {};
    cout << "Digite " << tam << " IDs para o subconjunto:" << endl;
    while ((int)ids.size() < tam) {
        char id_no = get_id_entrada();
        bool existe = false;
        for (No* no : grafo->lista_adj) {
            if (no->id == id_no) {
                existe = true;
                break;
            }
        }

        if (!existe) {
            cout << "Vertice nao existe. Tente novamente." << endl;
        } else {
            bool repetido = find(ids.begin(), ids.end(), id_no) != ids.end();
            if (repetido) {
                cout << "Valor repetido. Tente novamente." << endl;
            } else {
                ids.push_back(id_no);
            }
        }
    }
    return ids;
}

bool Gerenciador::pergunta_imprimir_arquivo(string nome_arquivo) {
    cout << endl << "Imprimir em arquivo externo? (" << nome_arquivo << ")" << endl;
    cout << "(1) Sim;" << endl;
    cout << "(2) Nao." << endl;
    int resp;
    cin >> resp;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << endl;

    switch (resp) {
        case 1:
            return true;
        case 2:
            return false;
        default:
            cout << "Resposta invalida. Por favor, digite 1 para Sim ou 2 para Nao." << endl;
            return pergunta_imprimir_arquivo(nome_arquivo);
    }
}

void Gerenciador::imprimir_vector_char(const vector<char>& vec) {
    if (vec.empty()) {
        cout << "Nenhum resultado." << endl;
        return;
    }
    for (size_t i = 0; i < vec.size(); ++i) {
        cout << vec[i];
        if (i < vec.size() - 1) {
            cout << ",";
        }
    }
    cout << endl << endl;
}

void Gerenciador::imprimir_grafo(Grafo* grafo) {
    if (grafo == nullptr || grafo->lista_adj.empty()) {
        cout << "Grafo vazio ou nulo." << endl;
        return;
    }
    for (No* no : grafo->lista_adj) {
        cout << no->id << ":";
        if (!no->arestas.empty()) {
            for (size_t i = 0; i < no->arestas.size(); ++i) {
                cout << " " << no->arestas[i]->id_no_alvo;
                if (grafo->in_ponderado_aresta) {
                    cout << "(" << no->arestas[i]->peso << ")";
                }
                if (i < no->arestas.size() - 1) {
                    cout << " ->";
                }
            }
        }
        cout << endl;
    }
    cout << endl;
}

void Gerenciador::imprimir_h_output(int raio, int diametro, const vector<char>& centro, const vector<char>& periferia) { 
    cout << "Raio: " << raio << endl; // Valor do raio 
    cout << "Diametro: " << diametro << endl; // Valor do diametro 

    cout << "Centro: "; // vector<char> do centro 
    if (centro.empty()) {
        cout << "Nenhum";
    } else {
        for (size_t i = 0; i < centro.size(); ++i) {
            cout << centro[i];
            if (i < centro.size() - 1) {
                cout << ",";
            }
        }
    }
    cout << endl;

    cout << "Periferia: "; // vector<char> da periferia 
    if (periferia.empty()) {
        cout << "Nenhum";
    } else {
        for (size_t i = 0; i < periferia.size(); ++i) {
            cout << periferia[i];
            if (i < periferia.size() - 1) {
                cout << ",";
            }
        }
    }
    cout << endl << endl;
}

int Gerenciador::solicitarInteiro(string mensagem, int ordem) {
    int valor_validado;
    string input_str;
    int min_val = 2;

    while (true) {
        cout << mensagem;
        getline(cin, input_str);

        try {
            valor_validado = stoi(input_str);

            if (valor_validado >= min_val && valor_validado <= ordem) {
                return valor_validado;
            } else {
                cout << "Valor fora do intervalo. Digite um numero entre "
                     << min_val << " e " << ordem << "." << endl;
            }
        }
        catch (invalid_argument&) {
            cout << "Entrada invalida. Digite um numero inteiro." << endl;
        }
        catch (out_of_range&) {
            cout << "Numero muito grande ou muito pequeno. Tente novamente." << endl;
        }
    }
}