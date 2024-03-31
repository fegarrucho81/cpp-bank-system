#include <iostream>
#include <random>
#include <vector>
#include <string>

using namespace std;

class Usuarios; // Forward declaration

class Banco {
private:
    string nomeUsuario, senha;
    double saldo;
    int numeroConta;

public:
    Banco() {
        nomeUsuario = " ";
        saldo = 0;
        gerarNumeroConta();
    }
    
    Banco(string nomeUsuario, double saldo) {
        this -> nomeUsuario = nomeUsuario;
        this -> saldo = saldo;
        gerarNumeroConta();
    }

    void setDadosUsuario(string nomeUsuario, int numeroConta, double saldo) {
        if(!nomeUsuario.empty() || numeroConta != 0) {
            this -> nomeUsuario = nomeUsuario;
            this -> numeroConta = numeroConta;
            this -> saldo = saldo;
        }
    }

    void setSenha(string novaSenha) {
        senha = novaSenha;
    }

    bool verificaSenha(string senhaDigitada) const {      
        return senha == senhaDigitada;
    }

    string getNomeUsuario() const {                                                               
        return nomeUsuario;
    }

    int getNumeroConta() const {
        return numeroConta;
    }

    double getSaldo() const {
        return saldo;
    }

    string solicitarNomeUsuario() {
        string nomeUsuario;
        cout << "Digite seu nome de usuário: " << endl;
        cin >> nomeUsuario;
        return nomeUsuario;
    }

    string solicitarSenha() {
        string senha;
        cout << "Digite sua senha: " << endl;
        cin >> senha;
        return senha;
    }   

    bool fazerLogin(Usuarios& usuarios); 

    void sacar(double valor) {
        if (valor > 0 && valor <= getSaldo()) {
            saldo -= valor;
            cout << "Saque realizado com sucesso no valor de: R$ " << valor << endl;
        }
    }

    void depositar(double valor) {
        if(valor > 0) {
            saldo += valor;
            cout << "Deposito realizado com sucesso no valor de: R$ " << valor << endl;
        }    
    }

    void informacoesConta() {
        cout << "Titular: " << getNomeUsuario() << endl;
        cout << "Numero da conta: " << getNumeroConta() << endl;
        cout << "Saldo: R$ " << getSaldo() << endl;
    }

    void gerarNumeroConta() {
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<int> distribuicao(1000,9999);

        numeroConta = distribuicao(gen);
    }

};

class Usuarios {
private:
    vector<Banco> contas;

public:
    void adicionarConta(string nomeUsuario, double saldoInicial) {
        Banco novaConta(nomeUsuario, saldoInicial);
        contas.push_back(novaConta);
    }

    void removerConta(int numeroConta) {
        for(auto i = contas.begin(); i != contas.end(); i++) {
            if(i -> getNumeroConta() == numeroConta) {
                contas.erase(i);
                cout << "Conta removida com sucesso!" << endl;
                return;
            }
        }
        cout << "Conta não encontrada" << endl;
    }

    void listarContas() {
        cout << "Listas de contas: " << endl;
        for(const auto& conta : contas) {
            cout << "Titular: " << conta.getNomeUsuario() << endl;
            cout << "Numero da conta: " << conta.getNumeroConta() << endl;
            cout << "Saldo: R$ " << conta.getSaldo() << endl;
        }
    }

    Banco* getConta(string nomeUsuario);

    bool transferirDinheiro(string origem, string destino, double valor);

};

class Testes {
public:
    static void testeTransferirDinheiro(Usuarios& usuarios) {
        cout << "INICIANDO TESTE DA FUNÇAO DE TRANSFERENCIA DE DINHEIRO" << endl;
        cout << "\n" << endl;

        usuarios.adicionarConta("Baby", 10000000);
        usuarios.adicionarConta("Babynha do baby", 1000000);

        cout << "Saldo antes da transferencia:" << endl;
        cout << "-----------------" << endl;
        usuarios.listarContas();
        cout << "-----------------" << endl;

        double valorTransferencia = 1000000;
        bool sucesso = usuarios.transferirDinheiro("Baby", "Babynha do baby", valorTransferencia);

        if (sucesso) {
            cout << "Transferencia bem-sucedida!" << endl;
        } else {
            cout << "Transferencia falhou." << endl;
        }

        cout << "Saldo apos a transferencia:" << endl;
        cout << "-----------------" << endl;
        usuarios.listarContas();
        cout << "-----------------" << endl;

        cout << "Fim do teste de transferencia de dinheiro." << endl;
    }

    // posso adicionar outros testes posteriormente


};

bool Banco::fazerLogin(Usuarios& usuarios) {
    string nomeUsuario = solicitarNomeUsuario();
    string senha = solicitarSenha();

    Banco* conta = usuarios.getConta(nomeUsuario);

    if(conta != nullptr && conta -> verificaSenha(senha)) {
        cout << "Login bem-sucedido!" << endl;
        return true;
    }
    else {
        cout << "Nome de usuário ou senha incorretos." << endl;
        return false;
    }
}

Banco* Usuarios::getConta(string nomeUsuario) {
    for (auto& conta : contas) {
        if (conta.getNomeUsuario() == nomeUsuario) {
            return &conta;
        }
    }
    return nullptr;
}

bool Usuarios::transferirDinheiro(string origem, string destino, double valor) {
    Banco* contaOrigemPtr = getConta(origem);
    Banco* contaDestinoPtr = getConta(destino);

    if (contaOrigemPtr == nullptr || contaDestinoPtr == nullptr) {
        cout << "Conta de origem ou destino nao encontradas." << endl;
        return false;
    }

    Banco& contaOrigem = *contaOrigemPtr;
    Banco& contaDestino = *contaDestinoPtr;

    if (contaOrigem.getSaldo() < valor) {
        cout << "Saldo insuficiente para transaçao." << endl;
        return false;
    }

    contaOrigem.sacar(valor);
    contaDestino.depositar(valor);

    cout << "Transferencia de R$ " << valor << " de " << origem << " para " << destino << " realizada com sucesso." << endl ;
    return true;
}

int main() {
    
    return 0;
}
