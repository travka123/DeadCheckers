#pragma once

class Processable {
protected:
	void RegisterProcessable();
	void UnregisterProcessable();

public:
	virtual void Process() = 0;
};