#include <Windows.h>
#include <wininet.h>
#include <netlistmgr.h>
#include <string>
#include <iostream>
#include <fstream>
#pragma comment(lib,"kernel32.lib")
#pragma comment(lib,"ole32.lib")
#pragma comment(lib,"wininet.lib")

using namespace std;

class cFuncoes
{
private:

	INetworkListManager* NetListMgr = 0;
	void InicializarInstancia()
	{
		CoInitializeEx(0, COINIT_MULTITHREADED);
		CoCreateInstance(CLSID_NetworkListManager, 0, CLSCTX_ALL, IID_INetworkListManager, (void**)&NetListMgr);
	}

public:

	bool VerificarConexaoComInternet()
	{
		bool bReturn = false;

		InicializarInstancia();

		HRESULT Result;//Caso seja necessário verificar status de tarefa de API.

		VARIANT_BOOL Valor = 0;
		Result = NetListMgr->get_IsConnectedToInternet((VARIANT_BOOL*)&Valor);
		
		if (Valor == -1)
		{
			BOOL Res = InternetCheckConnection(L"https://google.com", FLAG_ICC_FORCE_CONNECTION, 0);
			if (Res == TRUE)
				cout << "Você está conectado a internet.";
			else
				cout << "Não foi possível estabelecer uma conexão com a internet.";
		}
		else
			cout << "Você não está conectado a internet.";

		CoUninitialize();

		return bReturn;
	}

}Funcoes;

int main()
{
	cout << "O assistente está verificando se há conexão com a internet...";

	Funcoes.VerificarConexaoComInternet();

	system("pause");
}