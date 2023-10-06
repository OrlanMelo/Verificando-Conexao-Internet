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

		HRESULT Result;//Caso seja necess�rio verificar status de tarefa de API.

		VARIANT_BOOL Valor = 0;
		Result = NetListMgr->get_IsConnectedToInternet((VARIANT_BOOL*)&Valor);
		
		if (Valor == -1)
		{
			BOOL Res = InternetCheckConnection(L"https://google.com", FLAG_ICC_FORCE_CONNECTION, 0);
			if (Res == TRUE)
				cout << "Voc� est� conectado a internet.";
			else
				cout << "N�o foi poss�vel estabelecer uma conex�o com a internet.";
		}
		else
			cout << "Voc� n�o est� conectado a internet.";

		CoUninitialize();

		return bReturn;
	}

}Funcoes;

int main()
{
	cout << "O assistente est� verificando se h� conex�o com a internet...";

	Funcoes.VerificarConexaoComInternet();

	system("pause");
}