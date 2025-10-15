
template <>
AdjustableEngine<real_t>:: ~AdjustableEngine() noexcept
{

}


template <>
void AdjustableEngine<real_t>:: symmetrize() noexcept
{
    const size_t nvar = alpha.rows;
    for(size_t i=1;i<=nvar;++i)
    {
        for(size_t j=1;j<i;++j) alpha[i][j] = alpha[j][i];
    }
}
