#include "Calculator.h"
#include "Mcomplex.h"
class Tests
{
	public:
	static Tests getInstance();
	void run();
	protected:
	void complexT();
	void calculatorT();
	private:
	Tests()=default;
	Tests(const Tests& t)=default;
};
