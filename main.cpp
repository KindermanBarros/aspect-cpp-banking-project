#include <iostream>
#include <aspectc++.h>

class ContaBancaria {
protected:
    double saldo;
    std::string tipoConta;
    std::string tipoCliente;
    std::string dataAbertura;

public:
    ContaBancaria(const std::string& tipo, const std::string& cliente, const std::string& abertura)
        : saldo(0.0), tipoConta(tipo), tipoCliente(cliente), dataAbertura(abertura) {}

    virtual ~ContaBancaria() {}

    virtual void sacar(double valor) = 0;
    virtual void depositar(double valor) = 0;
    virtual void calcularTarifaManutencao() = 0;
};

class ContaPoupanca : public ContaBancaria {
public:
    ContaPoupanca(const std::string& cliente, const std::string& abertura)
        : ContaBancaria("Poupança", cliente, abertura) {}

    void sacar(double valor) override {
        // Implementação do saque para conta poupança
    }

    void depositar(double valor) override {
        // Implementação do depósito para conta poupança
    }

    void calcularTarifaManutencao() override {
        // Implementação do cálculo da tarifa de manutenção para conta poupança
    }
};

class ContaInvestimento : public ContaBancaria {
public:
    ContaInvestimento(const std::string& cliente, const std::string& abertura)
        : ContaBancaria("Investimento", cliente, abertura) {}

    void sacar(double valor) override {
        // Implementação do saque para conta investimento
    }

    void depositar(double valor) override {
        // Implementação do depósito para conta investimento
    }

    void calcularTarifaManutencao() override {
        // Implementação do cálculo da tarifa de manutenção para conta investimento
    }
};

aspect VerificacaoSaldoAspect {
    pointcut saqueExecution(ContaBancaria* conta, double valor) :
        execution(void ContaBancaria::sacar(double)) && target(conta) && args(valor);

    before(ContaBancaria* conta, double valor) : saqueExecution(conta, valor) {
        if (conta->saldo < valor) {
            std::cout << "Saldo insuficiente na conta " << conta->tipoConta << std::endl;
            // Ou gerar um log de erro conforme necessário
        }
    }
};

int main() {
    ContaPoupanca contaPoupanca("ClienteA", "2023-08-07");
    contaPoupanca.depositar(1000.0);
    contaPoupanca.sacar(500.0); // Aspecto será aplicado aqui

    ContaInvestimento contaInvestimento("ClienteB", "2023-08-07");
    contaInvestimento.depositar(2000.0);
    contaInvestimento.sacar(2500.0); // Aspecto será aplicado aqui

    return 0;
}
