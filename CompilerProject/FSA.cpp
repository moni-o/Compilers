enum Input{
    letter, //L
    digit,  //D
    asterick, //*
    slash,  //
    equal, // =
    lessthan, // <
    greatherthan, // >
    add, // +
    minus, // -
    comma, // ,
    lb, // {
    rb, // }
    lp, // (
    rp, // )
    semicolen, // ;
    carrot, // ^
    exclamation, // !
    count, 

};

enum States{
    newLine,
    error,
    mop_,
    state_3,
    integer,
    state5,
    var,
    state7,
    state8,
    state9,
    state10,
    assign,
    relopa,
    state14,
    relopx,
    relopy,
    state17,
    relopb,
    relopc,
    addState,
    minusState,
    comma_State,
    rb_State,
    lb_State,
    lp_State,
    rp_State,
    semi_State,
    carrot_State,
    exclamation_State,
    notEqual,
    count_State

};


int tableDriven[count_State][count]; //2D array

for(int i = 0; i <count_State, i+=){
    for(int j = 0; j<count, j++){
        tableDriven[i][j] = -1
    }
}

