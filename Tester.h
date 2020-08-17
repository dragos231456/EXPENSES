#pragma once
#include <assert.h>
#include "Service.h"
#include <fstream>

class Tester
{
private:
	void testDomain();

	void testDomainCreate();
	void testDomainUpdateDescription();
	void testDomainUpdatePhotoName();
	void testRead();
	void testWrite();

	/**/

	void testRepo();

	void testRepoRead();
	void testRepoAdd();
	void testRepoUpdate();

	/**/

	void testValidator();

	void testValidator___InvalidObject___returnFalse();
	void testValidator___ValidObject___returnTrue();

	/**/

	void testService();

	void testSerivce___Add___InvalidObject___ThrowError();
	void testService___Add___ValidObject__Success();
	void testService___Update__InvalidObject___ThrowError();
	void testService___Update__InvalidIndex___ThrowError();
	void testService___Update__ValidObject___Success();
public:
	Tester() {}
	void testAll();
};

