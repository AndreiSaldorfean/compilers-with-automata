#pragma once
#include <gtest/gtest.h>
#include "compiler.h"

class CompilerTest : public ::testing::Test
{
protected:
    Compiler compiler;
    void SetUp() override;
    void TearDown() override;
};
