#include "test_compiler.h"

/*I am still learining this framework and i will leave these just for a template*/
void CompilerTest::SetUp() {}

void CompilerTest::TearDown() {}
/*I am still learining this framework and i will leave these just for a template*/


/*=================================================================================================*/
/*                                        Positive Test Cases                                      */
/*=================================================================================================*/

/**
*  @brief Test correct input parameters
*  @cond Positive
*/
TEST_F(CompilerTest, AnalyzeLine_CorrectInput_Param1)
{
    EXPECT_TRUE(compiler.parseGrammer("../resources/test_set_1/test_grammar.txt"));
    EXPECT_TRUE(compiler.parseActions("../resources/test_set_1/test_actions.txt"));
    EXPECT_TRUE(compiler.parseJump("../resources/test_set_1/test_goto.txt"));

    EXPECT_TRUE(compiler.analyzeLine("id"));
}

/**
*  @brief Test correct input parameters
*  @cond Positive
*/
TEST_F(CompilerTest, AnalyzeLine_CorrectInput_Param2)
{
    EXPECT_TRUE(compiler.parseGrammer("../resources/test_set_1/test_grammar.txt"));
    EXPECT_TRUE(compiler.parseActions("../resources/test_set_1/test_actions.txt"));
    EXPECT_TRUE(compiler.parseJump("../resources/test_set_1/test_goto.txt"));

    EXPECT_TRUE(compiler.analyzeLine("id*id"));
}

/**
*  @brief Test correct input parameters
*  @cond Positive
*/
TEST_F(CompilerTest, AnalyzeLine_CorrectInput_Param3)
{
    EXPECT_TRUE(compiler.parseGrammer("../resources/test_set_1/test_grammar.txt"));
    EXPECT_TRUE(compiler.parseActions("../resources/test_set_1/test_actions.txt"));
    EXPECT_TRUE(compiler.parseJump("../resources/test_set_1/test_goto.txt"));

    EXPECT_TRUE(compiler.analyzeLine("id+id+(id+id)"));
}

/**
*  @brief Test correct input parameters
*  @cond Positive
*/
TEST_F(CompilerTest, AnalyzeLine_CorrectInput_Param4)
{
    EXPECT_TRUE(compiler.parseGrammer("../resources/test_set_1/test_grammar.txt"));
    EXPECT_TRUE(compiler.parseActions("../resources/test_set_1/test_actions.txt"));
    EXPECT_TRUE(compiler.parseJump("../resources/test_set_1/test_goto.txt"));

    EXPECT_TRUE(compiler.analyzeLine("(id+id+(id+id))"));
}

/**
*  @brief Test correct input parameters
*  @cond Positive
*/
TEST_F(CompilerTest, AnalyzeLine_CorrectInput_Param5)
{
    EXPECT_TRUE(compiler.parseGrammer("../resources/test_set_1/test_grammar.txt"));
    EXPECT_TRUE(compiler.parseActions("../resources/test_set_1/test_actions.txt"));
    EXPECT_TRUE(compiler.parseJump("../resources/test_set_1/test_goto.txt"));

    EXPECT_TRUE(compiler.analyzeLine("id*id+(id*id)"));
}

/**
*  @brief Test correct input parameters
*  @cond Positive
*/
TEST_F(CompilerTest, AnalyzeLine_CorrectInput_Param6)
{
    EXPECT_TRUE(compiler.parseGrammer("../resources/test_set_1/test_grammar.txt"));
    EXPECT_TRUE(compiler.parseActions("../resources/test_set_1/test_actions.txt"));
    EXPECT_TRUE(compiler.parseJump("../resources/test_set_1/test_goto.txt"));

    EXPECT_TRUE(compiler.analyzeLine("(id*id+(id*id))"));
}

/**
*  @brief Test correct input parameters
*  @cond Positive
*/
TEST_F(CompilerTest, AnalyzeLine_CorrectInput_Param7)
{
    EXPECT_TRUE(compiler.parseGrammer("../resources/test_set_1/test_grammar.txt"));
    EXPECT_TRUE(compiler.parseActions("../resources/test_set_1/test_actions.txt"));
    EXPECT_TRUE(compiler.parseJump("../resources/test_set_1/test_goto.txt"));

    EXPECT_TRUE(compiler.analyzeLine("(id*(id)+(id*id))"));
}

/**
*  @brief Test correct input parameters
*  @cond Positive
*/
TEST_F(CompilerTest, AnalyzeLine_CorrectInput_Param8)
{
    EXPECT_TRUE(compiler.parseGrammer("../resources/test_set_1/test_grammar.txt"));
    EXPECT_TRUE(compiler.parseActions("../resources/test_set_1/test_actions.txt"));
    EXPECT_TRUE(compiler.parseJump("../resources/test_set_1/test_goto.txt"));

    EXPECT_TRUE(compiler.analyzeLine("(id*(id)+(id*id))"));
}

/**
*  @brief Test correct input parameters
*  @cond Positive
*/
TEST_F(CompilerTest, AnalyzeLine_CorrectInput_Param9)
{
    EXPECT_TRUE(compiler.parseGrammer("../resources/test_set_1/test_grammar.txt"));
    EXPECT_TRUE(compiler.parseActions("../resources/test_set_1/test_actions.txt"));
    EXPECT_TRUE(compiler.parseJump("../resources/test_set_1/test_goto.txt"));

    EXPECT_TRUE(compiler.analyzeLine("id*(id)+(id*id)"));
}

/**
*  @brief Test correct input parameters
*  @cond Positive
*/
TEST_F(CompilerTest, AnalyzeLine_CorrectInput_Param10)
{
    EXPECT_TRUE(compiler.parseGrammer("../resources/test_set_1/test_grammar.txt"));
    EXPECT_TRUE(compiler.parseActions("../resources/test_set_1/test_actions.txt"));
    EXPECT_TRUE(compiler.parseJump("../resources/test_set_1/test_goto.txt"));

    EXPECT_TRUE(compiler.analyzeLine("((id))"));
}

/**
*  @brief Test correct input parameters
*  @cond Positive
*/
TEST_F(CompilerTest, AnalyzeLine_CorrectInput_Param11)
{
    EXPECT_TRUE(compiler.parseGrammer("../resources/test_set_1/test_grammar.txt"));
    EXPECT_TRUE(compiler.parseActions("../resources/test_set_1/test_actions.txt"));
    EXPECT_TRUE(compiler.parseJump("../resources/test_set_1/test_goto.txt"));

    EXPECT_TRUE(compiler.analyzeLine("((id)+(id))"));
}

/**
*  @brief Test correct input parameters
*  @cond Positive
*/
TEST_F(CompilerTest, AnalyzeLine_CorrectInput_Param12)
{
    EXPECT_TRUE(compiler.parseGrammer("../resources/test_set_1/test_grammar.txt"));
    EXPECT_TRUE(compiler.parseActions("../resources/test_set_1/test_actions.txt"));
    EXPECT_TRUE(compiler.parseJump("../resources/test_set_1/test_goto.txt"));

    EXPECT_TRUE(compiler.analyzeLine("(((id)+id))"));
}
/*=================================================================================================*/
/*                                        Negative Test Cases                                      */
/*=================================================================================================*/

/**
*  @brief Test empty files
*  @cond Negative
*/
TEST_F(CompilerTest, AnalizeLine_WrongInput_EmptyFiles)
{
    EXPECT_FALSE(compiler.parseGrammer("../resources/test_set_2/test_grammar.txt"));
    EXPECT_FALSE(compiler.parseActions("../resources/test_set_2/test_actions.txt"));
    EXPECT_FALSE(compiler.parseJump("../resources/test_set_2/test_goto.txt"));

    EXPECT_FALSE(compiler.analyzeLine("id+id"));
}

/**
*  @brief Test incorrect actions table
*  @cond Negative
*/
TEST_F(CompilerTest, AnalizeLine_WrongInput_IncorrectActionsTable)
{
    EXPECT_TRUE(compiler.parseActions("../resources/test_set_3/test_actions.txt"));
    EXPECT_TRUE(compiler.parseGrammer("../resources/test_set_3/test_grammar.txt"));
    EXPECT_TRUE(compiler.parseJump("../resources/test_set_3/test_goto.txt"));

    EXPECT_FALSE(compiler.analyzeLine("id+id"));
}

/**
*  @brief Test incorrect grammar
*  @cond Negative
*/
TEST_F(CompilerTest, AnalizeLine_WrongInput_IncorrectGrammar)
{
    EXPECT_TRUE(compiler.parseActions("../resources/test_set_4/test_actions.txt"));
    EXPECT_TRUE(compiler.parseGrammer("../resources/test_set_4/test_grammar.txt"));
    EXPECT_TRUE(compiler.parseJump("../resources/test_set_4/test_goto.txt"));

    EXPECT_FALSE(compiler.analyzeLine("id+id"));
}

/**
*  @brief Test incorrect goto table
*  @cond Negative
*/
TEST_F(CompilerTest, AnalizeLine_WrongInput_IncorrectGoto)
{
    EXPECT_TRUE(compiler.parseActions("../resources/test_set_5/test_actions.txt"));
    EXPECT_TRUE(compiler.parseGrammer("../resources/test_set_5/test_grammar.txt"));
    EXPECT_TRUE(compiler.parseJump("../resources/test_set_5/test_goto.txt"));

    EXPECT_FALSE(compiler.analyzeLine("id+id"));
}

/**
*  @brief Test incorrect expression
*  @cond Negative
*/
TEST_F(CompilerTest, AnalizeLine_WrongInput_Expression1)
{
    EXPECT_TRUE(compiler.parseActions("../resources/test_set_1/test_actions.txt"));
    EXPECT_TRUE(compiler.parseGrammer("../resources/test_set_1/test_grammar.txt"));
    EXPECT_TRUE(compiler.parseJump("../resources/test_set_1/test_goto.txt"));

    EXPECT_FALSE(compiler.analyzeLine("id.id"));
}

/**
*  @brief Test incorrect expression
*  @cond Negative
*/
TEST_F(CompilerTest, AnalizeLine_WrongInput_Expression2)
{
    EXPECT_TRUE(compiler.parseActions("../resources/test_set_1/test_actions.txt"));
    EXPECT_TRUE(compiler.parseGrammer("../resources/test_set_1/test_grammar.txt"));
    EXPECT_TRUE(compiler.parseJump("../resources/test_set_1/test_goto.txt"));

    EXPECT_FALSE(compiler.analyzeLine("id-(id)"));
}