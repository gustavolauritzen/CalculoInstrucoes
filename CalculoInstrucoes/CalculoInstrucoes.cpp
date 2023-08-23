#include <iostream>
#include <fstream>
#include <string>

// Desenvolvido por Matheus Baron Lauritzen e Gustavo Baron Lauritzen

using namespace std;

struct Organizacao {
	float cpiU, cpiJ, cpiB, cpiIL, cpiIAE, cpiR, cpiS, totalCiclos, contadorInstrucao, mediaCPI, tempoClock, freq, tempoExecucaoCPU;
};

struct Instrucao {
	string opCode;
};

void calcularImprimirDesempenho(Organizacao& orgA, Organizacao& orgB) {

	//Calculando a media de CPI organizacao A
	orgA.mediaCPI = orgA.totalCiclos / orgA.contadorInstrucao;

	//Calculando o tempo de execucao organizacao A
	orgA.tempoExecucaoCPU = orgA.totalCiclos * orgA.tempoClock;

	//Calculando a media de CPI organizacao B
	orgB.mediaCPI = orgB.totalCiclos / orgB.contadorInstrucao;

	//Calculando o tempo de execucao organizacao A
	orgB.tempoExecucaoCPU = orgB.totalCiclos * orgB.tempoClock;

	system("cls");

	cout << "Total de ciclos Organizacao A:" << endl;
	cout << orgA.totalCiclos << endl;
	cout << "Media de CPI Organizacao A:" << endl;
	cout << orgA.mediaCPI << endl;

	cout << "Total de ciclos Organizacao B:" << endl;
	cout << orgB.totalCiclos << endl;
	cout << "Media de CPI Organizacao B:" << endl;
	cout << orgB.mediaCPI << endl;

	if (orgA.tempoExecucaoCPU > orgB.tempoExecucaoCPU) {
		cout << "A organizacao B e " << orgA.tempoExecucaoCPU / orgB.tempoExecucaoCPU << " vezes mais rapido que a organizacao A" << endl;
	}
	else if (orgB.tempoExecucaoCPU > orgA.tempoExecucaoCPU) {
		cout << "A organizacao A e " << orgB.tempoExecucaoCPU / orgA.tempoExecucaoCPU << " vezes mais rapido que a organizacao B" << endl;
	}
	else {
		cout << "As duas organizacoes tem o mesmo desempenho" << endl;
	}

	system("pause");

}

//  ndice baseado em 0 do primeiro caractere que voc  deseja pegar e  ndice baseado em 0 do  ltimo caractere que voc  deseja pegar
void leBinarioArquivo(Organizacao& org, string nomeArquivo) {
	ifstream file(nomeArquivo);
	int start = 25;
	int end = 31;
	org.contadorInstrucao = 0;
	org.mediaCPI = 0;
	org.totalCiclos = 0;
	Instrucao instrucao;

	if (!file.is_open()) {
		cout << "N o foi poss vel abrir o arquivo." << endl;
		return;
	}

	string line;
	while (getline(file, line)) {

		if (start >= 0 && end < line.length()) {
			instrucao.opCode = line.substr(start, end - start + 1);
			if (instrucao.opCode == "0110111" || instrucao.opCode == "0010111") {
				org.totalCiclos = org.totalCiclos + org.cpiU;
				org.contadorInstrucao++;
			}
			else if (instrucao.opCode == "1101111" || instrucao.opCode == "1100111") {
				org.totalCiclos = org.totalCiclos + org.cpiJ;
				org.contadorInstrucao++;
			}
			else if (instrucao.opCode == "1100011") {
				org.totalCiclos = org.totalCiclos + org.cpiB;
				org.contadorInstrucao++;
			}
			else if (instrucao.opCode == "0000011") {
				org.totalCiclos = org.totalCiclos + org.cpiIL;
				org.contadorInstrucao++;
			}
			else if (instrucao.opCode == "0100011") {
				org.totalCiclos = org.totalCiclos + org.cpiS;
				org.contadorInstrucao++;
			}
			else if (instrucao.opCode == "0010011" || instrucao.opCode == "1110011") {
				org.totalCiclos = org.totalCiclos + org.cpiIAE;
				org.contadorInstrucao++;
			}
			else if (instrucao.opCode == "0110011") {
				org.totalCiclos = org.totalCiclos + org.cpiR;
				org.contadorInstrucao++;
			}
		}
		else {
			cout << "Intervalo fora dos limites da linha." << endl;
		}
	}



	file.close();
}

void menuEntradaDadosOrg(Organizacao& org) {
	cout << "Informe o numero de ciclos por instrucao do tipo U:" << endl;
	cin >> org.cpiU;
	cout << "Informe o numero de ciclos por instrucao do tipo J:" << endl;
	cin >> org.cpiJ;
	cout << "Informe o numero de ciclos por instrucao do tipo B:" << endl;
	cin >> org.cpiB;
	cout << "Informe o numero de ciclos por instrucao do tipo I para loads:" << endl;
	cin >> org.cpiIL;
	cout << "Informe o numero de ciclos por instrucao do tipo I para aritmetica e ecall:" << endl;
	cin >> org.cpiIAE;
	cout << "Informe o numero de ciclos por instrucao do tipo R:" << endl;
	cin >> org.cpiR;
	cout << "Informe o numero de ciclos por instrucao do tipo S:" << endl;
	cin >> org.cpiS;
	cout << "Informe o tempo de relogio:" << endl;
	cin >> org.tempoClock;
}

void gerenciarCalculoInstrucoes() {
	Organizacao orgA, orgB;
	cout << "Informe os dados para a Organizacao A:" << endl;
	menuEntradaDadosOrg(orgA);
	cout << "Informe os dados para a Organizacao B:" << endl;
	menuEntradaDadosOrg(orgB);
	leBinarioArquivo(orgA, "DumpBinario.txt");
	leBinarioArquivo(orgB, "DumpBinario.txt");
	calcularImprimirDesempenho(orgA, orgB);
}

//Menu inicial
int menuInicial() {
	int escolhaMenuInicial;
	do {
		cout << "Bem vindo ao Calculo de Instrucoes" << endl;
		cout << "1 - Entrar" << endl;
		cout << "2 - Sair" << endl;
		cin >> escolhaMenuInicial;
		switch (escolhaMenuInicial) {
		case 1:
			system("cls");
			gerenciarCalculoInstrucoes();
			return 0;
			break;
		case 2:
			system("cls");
			return 0;
			break;
		default:
			cout << "Opcao invalida. Tente novamente." << endl;
			system("pause");
			system("cls");
		}
	} while (escolhaMenuInicial != 1 || escolhaMenuInicial != 2);
	return 0;
}

int main() {
	menuInicial();
	return 0;
}
