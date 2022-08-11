#include <Onyx/Dice/Dice.h>

DEFINE_SPEC(DiceSpec, "Onyx.Dice", EAutomationTestFlags::ProductFilter | EAutomationTestFlags::ApplicationContextMask)

struct FRollManyRangeTestCase
{
	FString Input;
	int Min;
	int Max;
};

struct FRollRangeTestCase
{
	int Input;
	int Min;
	int Max;
};

void DiceSpec::Define()
{
	Describe("RollMany", [this]()
	{
		It("should return right range", [this]()
		{
			TArray<FRollManyRangeTestCase> RollRangeTestCases;
			RollRangeTestCases.Emplace(FRollManyRangeTestCase{
				"1d1",
				1,
				1,
			});
			RollRangeTestCases.Emplace(FRollManyRangeTestCase{
				"2d1",
				2,
				2,
			});
			RollRangeTestCases.Emplace(FRollManyRangeTestCase{
				"1d2",
				1,
				2
			});
			RollRangeTestCases.Emplace(FRollManyRangeTestCase{
				"2d2",
				2,
				4
			});
			RollRangeTestCases.Emplace(FRollManyRangeTestCase{
				"4d4",
				4,
				16
			});
			RollRangeTestCases.Emplace(FRollManyRangeTestCase{
				"5d9",
				5,
				45
			});
			RollRangeTestCases.Emplace(FRollManyRangeTestCase{
				"10d10",
				10,
				100
			});
			for (auto RollTestCase : RollRangeTestCases)
			{
				const auto [Rolls, Result] = Dice::RollMany(RollTestCase.Input);
				TestTrue("Min", Result >= RollTestCase.Min);
				TestTrue("Max", Result <= RollTestCase.Max);
			}
		});
	});

	Describe("RollMany with an invalid roll input", [this]()
	{
		It("should return exception", [this]()
		{
			TArray<FString> InvalidInputs;
			InvalidInputs.Emplace("cd1");
			InvalidInputs.Emplace("0d1");
			InvalidInputs.Emplace("1d0");
			InvalidInputs.Emplace("111");
			InvalidInputs.Emplace("aaa");
			InvalidInputs.Emplace("-1d10");
			InvalidInputs.Emplace("1d-10");
			for (const auto& InvalidInput : InvalidInputs)
			{
				try
				{
					Dice::RollMany(InvalidInput);
					TestTrue("Should throw exception", false);
				}
				catch (FString error)
				{
					FString expectedError = "Roll " + InvalidInput + " is not valid.";
					TestEqual("Expected Error", error, expectedError);
				}
			}
		});
	});

	Describe("Roll", [this]()
	{
		It("should return correct range", [this]()
		{
			TArray<FRollRangeTestCase> RollRangeTestCases;
			RollRangeTestCases.Emplace(FRollRangeTestCase{
				1,
				1,
				1,
			});
			for (auto RollRangeTestCase : RollRangeTestCases)
			{
				Dice d = Dice(RollRangeTestCase.Input);
				int roll = d.Roll();
				TestTrue("Min", roll >= RollRangeTestCase.Min);
				TestTrue("Max", roll <= RollRangeTestCase.Max);
			}
		});
	});
}
