//given:- (Every Minute) Implied volatilities(IVs) BankNifty and Nifty
//     :- TTE(time to expiry) in years
//     :- 690512 rows and 3 columns
//     :- 9:15 to 15:30


//Focus :- Missing values present
//      :- p_l values depend on spread and IV values

//Formula used:-  Spread = IV_BankNifty - IV_Nifty
//            :-  p_l = Spread*(TTE)^0.7


///1. Build a z-score based trading system. It would use the z-scores of the spread to identify when volatility has diverged away from the historical mean and act accordingly. The calculation of the P/L here constitutes the base model.
///2. Build a better model than the z-score trading system
///3. Compare and optimize the absolute P/L, sharpe ratio and Drawdown

