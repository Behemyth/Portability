import std;
import synodic.honesty.test;

import synodic.portability;

using namespace honesty::test;
using namespace honesty::test::literals;

namespace
{
	Suite SUITE(
		"backend",
		[]() -> Generator
		{
			co_yield "built_in"_test = [](const Requirements& requirements)
			{
				requirements.Expect(true);
			};
		});
	SuiteRegistrar _(SUITE);
}
