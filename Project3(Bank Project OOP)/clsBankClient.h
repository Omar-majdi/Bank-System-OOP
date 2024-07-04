#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "clsPerson.h"
#include "clsString.h"
#include "clsUtil.h"

using namespace std;


class clsBankClient : public clsPerson{
private:
	//The Obj Mode
	enum enMode {EmptyMode = 0, UpdateMode = 1, AddNewMode = 2};
	enMode _Mode;

	string _AccountNumber;
	string _PinCode;
	double _AccountBalance;
	bool _MarkedForDelete = false;


	//Abstraction
	// we should make it static cuz the find client is static and it uses this function 
	// Remmember: static functions can call just static functions
	static clsBankClient _ConvertLinetoClientObject(string Line, string Seperator = "#//#") {
		vector <string> vClientData;
		vClientData = clsString::Split(Line, Seperator);
		return clsBankClient(enMode::UpdateMode, vClientData[0], vClientData[1], vClientData[2], 
					vClientData[3], vClientData[4], vClientData[5], stod(vClientData[6]));
	}

	static string _ConvertClientObjectToLine(clsBankClient Client, string Seperator = "#//#") {
		string stClientRecord = "";
		stClientRecord += Client.FirstName + Seperator;
		stClientRecord += Client.LastName + Seperator;
		stClientRecord += Client.Email + Seperator;
		stClientRecord += Client.Phone + Seperator;
		stClientRecord += Client.AccountNumber() + Seperator;
		stClientRecord += Client.PinCode + Seperator;
		stClientRecord += to_string(Client.AccountBalance);

		return stClientRecord;
	}

	static clsBankClient _GetEmptyClientObject() {
		return clsBankClient(enMode::EmptyMode, "", "", "", "", "", "", 0);
	}

	static vector<clsBankClient> _LoadClientsDataFromFile() {
		vector <clsBankClient> vClients;

		fstream MyFile;
		MyFile.open("Clients.txt", ios::in);

		if (MyFile.is_open()) {
			string Line;
			while (getline(MyFile, Line)) {
				clsBankClient Client = _ConvertLinetoClientObject(Line);
				vClients.push_back(Client);
			}
			MyFile.close();
		}
		return vClients;
	}

	static void _SaveCleintsDataToFile(vector <clsBankClient> vClients) {
		fstream MyFile;

		MyFile.open("Clients.txt", ios::out);

		string DataLine;
		if (MyFile.is_open()) {
			for (clsBankClient& C : vClients) {
				if (!C.MarkedForDeleted()) {
					DataLine = _ConvertClientObjectToLine(C);
					MyFile << DataLine << endl;
				}
			}
			MyFile.close();
		}
	}

	void _Update() {
		vector <clsBankClient> _vClients;
		_vClients = _LoadClientsDataFromFile();

		for (clsBankClient& C : _vClients) {
			if (C.AccountNumber() == AccountNumber()) {
				// C is the Object in the file, and the this pointer is pointing on the object that we made with new information
				C = *this;
				break;
			}
		}
		_SaveCleintsDataToFile(_vClients);
	}

	void _AddNew() {
		_AddDataLineToFile(_ConvertClientObjectToLine(*this));
	}

	void _AddDataLineToFile(string stDataLine) {
		fstream MyFile;
		MyFile.open("Clients.txt", ios::out | ios::app);

		if (MyFile.is_open()) {
			MyFile << stDataLine << endl;
			MyFile.close();
		}
	}

	 string _PrepareTransferLogRecord(float Amount, clsBankClient& DestinationClient, string UserName, string Seperator = "#//#") {
		string RecordLine = "";
		RecordLine += clsDate::GetSystemDateTimeString() + Seperator;
		RecordLine += AccountNumber() + Seperator;
		RecordLine += DestinationClient.AccountNumber() + Seperator;
		RecordLine += to_string(Amount) + Seperator;
		RecordLine += to_string(AccountBalance) + Seperator;
		RecordLine += to_string(DestinationClient.AccountBalance) + Seperator;
		RecordLine += UserName;
		return RecordLine;
	 }

	 void _RegisterTransferLog(float TransferAmount, clsBankClient DestinationClient, string UserName) {
		 fstream MyFile;

		 MyFile.open("TransferLog.txt", ios::out | ios::app);

		 if (MyFile.is_open()) {
			 string DataLine = _PrepareTransferLogRecord(TransferAmount, DestinationClient, UserName);
			 MyFile << DataLine << endl;
			 MyFile.close();
		 }
	 }

	 struct stTransferLogRecord;

	 static stTransferLogRecord _ConvertTransferLogLineToRecord(string Line, string Seperatro = "#//#") {
		 stTransferLogRecord TransferLogRecord;

		 vector <string> vTrnsferLogRecordLine = clsString::Split(Line, Seperatro);
		 TransferLogRecord.DateTime = vTrnsferLogRecordLine[0];
		 TransferLogRecord.SourceAccountNumber = vTrnsferLogRecordLine[1];
		 TransferLogRecord.DestinationAccountNumber = vTrnsferLogRecordLine[2];
		 TransferLogRecord.Amount = stod(vTrnsferLogRecordLine[3]);
		 TransferLogRecord.srcBalanceAfter = stod(vTrnsferLogRecordLine[4]);
		 TransferLogRecord.destBalanceAfter = stod(vTrnsferLogRecordLine[5]);
		 TransferLogRecord.UserName = vTrnsferLogRecordLine[6];

		 return TransferLogRecord;

	 }
public:
	struct stTransferLogRecord {
		string DateTime;
		string SourceAccountNumber;
		string DestinationAccountNumber;
		float Amount;
		float srcBalanceAfter;
		float destBalanceAfter;
		string UserName;
	};

	clsBankClient(enMode Mode, string FirstName, string LastName, string Email, string Phone, string AccountNumber, string PinCode, double AccountBalance) : 
				clsPerson(FirstName, LastName, Email, Phone) {
		_Mode = Mode;
		_AccountBalance = AccountBalance;
		_AccountNumber = AccountNumber;
		_PinCode = PinCode;
	}

	bool IsEmpty() {
		return (_Mode == enMode::EmptyMode);
	}

	bool MarkedForDeleted() {
		return _MarkedForDelete;
	}

	string AccountNumber() {
		return _AccountNumber;
	}

	void setPinCode(string PinCode) {
		_PinCode = PinCode;
	}

	string GetPinCode() {
		return _PinCode;
	}

	__declspec(property(get = GetPinCode, put = setPinCode)) string PinCode;

	void setAccountBalance(double AccountBalance) {
		_AccountBalance = AccountBalance;
	}

	double GetAccountBalance() {
		return _AccountBalance;
	}

	__declspec(property(get = GetAccountBalance, put = setAccountBalance)) double AccountBalance;

	static clsBankClient Find(string AccountNumber) {
		vector <clsBankClient> vClients;

		fstream MyFile;
		MyFile.open("Clients.txt", ios::in);

		if (MyFile.is_open()) {
			string Line;
			while (getline(MyFile, Line)) {
				clsBankClient Client = _ConvertLinetoClientObject(Line);
				if (Client._AccountNumber == AccountNumber) {
					MyFile.close();
					return Client;
				}
				vClients.push_back(Client);
			}
			MyFile.close();
		}
		return _GetEmptyClientObject();
	}

	static clsBankClient Find(string AccountNumber, string PinCode) {
		vector <clsBankClient> vClients;

		fstream MyFile;
		MyFile.open("Clients.txt", ios::in);

		if (MyFile.is_open()) {
			string Line;
			while (getline(MyFile, Line)) {
				clsBankClient Client = _ConvertLinetoClientObject(Line);
				if (Client._AccountNumber == AccountNumber && Client._PinCode == PinCode) {
					MyFile.close();
					return Client;
				}
				vClients.push_back(Client);
			}
			MyFile.close();
		}
		return _GetEmptyClientObject();
	}

	enum enSaveResults { svFaildEmptyObject = 0, svSucceeded = 1, svFaildAccountNumberExists = 2 };

	enSaveResults Save() {
		switch (_Mode) {
		case enMode::EmptyMode:
			return enSaveResults::svFaildEmptyObject;
			break;

		case enMode::UpdateMode:
			_Update();
			return enSaveResults::svSucceeded;
			break;

		case enMode::AddNewMode:
		{
			if (clsBankClient::IsClientExist(_AccountNumber)) {
				return enSaveResults::svFaildAccountNumberExists;
			}
			else {
				_AddNew();
				_Mode = enMode::UpdateMode;
				return enSaveResults::svSucceeded;
			}
		}
		}

	}

	static bool IsClientExist(string AccountNumber) {
		clsBankClient Client1 = clsBankClient::Find(AccountNumber);
		return (!Client1.IsEmpty());
	}

	static clsBankClient GetAddNewClientObject(string AccountNumber) {
		return clsBankClient(enMode::AddNewMode, "", "", "", "", AccountNumber, "", 0);
	}

	bool Delete() {
		vector <clsBankClient> _vClients;
		_vClients = _LoadClientsDataFromFile();

		for (clsBankClient& C : _vClients) {
			if (C.AccountNumber() == _AccountNumber) {
				C._MarkedForDelete = true;
				break;
			}
		}

		_SaveCleintsDataToFile(_vClients);
		*this = _GetEmptyClientObject();
		return true;
	}

	static vector <clsBankClient> GetClientsList() {
		return _LoadClientsDataFromFile();
	}

	void Deposit(double Amount) {
		_AccountBalance += Amount;
		Save();
	}

	bool Withdraw(double Amount) {
		if (Amount > _AccountBalance)
			return false;
		else {
			_AccountBalance -= Amount;
			Save();
			return true;
		}
	}

	static double GetTotalBalances() {
		vector <clsBankClient> vClients = clsBankClient::GetClientsList();
		double TotalBalances = 0;

		for (clsBankClient& C : vClients)
			TotalBalances += C.AccountBalance;
		return TotalBalances;
	}

	bool Transfer(float Amount, clsBankClient& DestinationClient, string UserName) {
		if (Amount > AccountBalance)
			return false;

		Withdraw(Amount);
		DestinationClient.Deposit(Amount);
		_RegisterTransferLog(Amount, DestinationClient, UserName);
		return true;
	}

	static vector <stTransferLogRecord> GetTransfersLogList() {
		vector <stTransferLogRecord> vTransferLogRecord;

		fstream MyFile;
		MyFile.open("TransferLog.txt", ios::in);//Read Mode

		if (MyFile.is_open()) {
			string Line;

			stTransferLogRecord TransferRecord;

			while (getline(MyFile, Line)) {
				TransferRecord = _ConvertTransferLogLineToRecord(Line);
				vTransferLogRecord.push_back(TransferRecord);
			}
			MyFile.close();
		}
		return vTransferLogRecord;
	}
};

