#include <iostream>
#include <iomanip>
#include <stdio.h>
#include <stdint.h>
#include <mpir.h>
#include <stdlib.h>
#include <string.h>
#include <cmath>
#include <chrono>
#include <ctime>

using namespace std;

const int MAX_ITERATIONS = 100;
const int PLACES         = 1000000;        // desired decimal places
const int PRECISION      = PLACES + 1;  // +1 for the digit 3 before the decimal

const int BASE       = 10;  // base 10 numbers
const int BIT_COUNT  = 8;   // bits per machine word

const int BLOCK_SIZE = 10;                // print digits in blocks
const int LINE_SIZE  = 100;               // digits to print per line
const int LINE_COUNT = 10;  // lines to print
const int GROUP_SIZE = 5;                 // line grouping size

/**
 * Compute the cube root of a positive integer.
 * @param x where to store the result.
 * @param a the number whose cube root to compute.
 */
void cube_root(mpf_t& x, const mpf_t a);

/***** Add more functions as necessary. *****/
/**
 * Print the digits of the number in blocks of 10 digits and groups of 5 rows,
 * 500 digits total per row group
 * @param pi the number to be printed
 */
void print(const mpf_t pi);

/**
 * The main.
 */
int main()
{
    using namespace chrono;
    mpf_set_default_prec(BIT_COUNT*PRECISION);  // precision in bits

    mpir_ui one_ui = 1;						// setting value one for later computatzion
    mpir_ui two_ui = 2;						// setting value two for later computation
    mpir_ui three_ui = 3;					// setting value three for later computation

    //converting numbers to mpf_t data type
    mpf_t one; mpf_init_set_d(one, 1.0);
    mpf_t two; mpf_init_set_d(two, 2.0);
    mpf_t three; mpf_init_set_d(three, 3.0);
    mpf_t nine; mpf_init_set_d(nine, 9.0);
    mpf_t twenty_seven; mpf_init_set_d(twenty_seven, 27.0);

    // decalring variables for calculating the inital value of a
    mpf_t a_initial; mpf_init(a_initial);

    // calculating the initial value of a
    mpf_ui_div(a_initial, one_ui, three);

    // decalring variables for calculating the inital value of r
    mpf_t r_root_three; mpf_init(r_root_three);
    mpf_t r_numerator; mpf_init(r_numerator);
    mpf_t r_initial; mpf_init(r_initial);

    // calculating initial value of r
    mpf_sqrt_ui(r_root_three, three_ui);
    mpf_sub(r_numerator, r_root_three, one);
    mpf_div(r_initial, r_numerator, two);

    // decalring variables for calculating the inital value of s
    mpf_t s_r_cube; mpf_init(s_r_cube);
    mpf_t s_initial_one_minus_r_cube; mpf_init(s_initial_one_minus_r_cube);
    mpf_t s_initial; mpf_init(s_initial);

    // calculating initial value of s
    mpf_pow_ui(s_r_cube, r_initial, three_ui);
    mpf_sub(s_initial_one_minus_r_cube, one, s_r_cube);
    cube_root(s_initial, s_initial_one_minus_r_cube);
    

	//setting initial variables
    mpf_t a; mpf_init(a); mpf_set(a, a_initial);
    mpf_t r; mpf_init(r); mpf_set(r, r_initial);
    mpf_t s; mpf_init(s); mpf_set(s, s_initial);
    
    // initialising all variabless required for computing t
    mpf_t t; mpf_init(t);
    mpf_t t_r_times_two; mpf_init(t_r_times_two);
    
    // initialising all variables required for computing u
    mpf_t u; mpf_init(u); 
    mpf_t u_r_sqaure; mpf_init(u_r_sqaure); 
    mpf_t u_r_sqaure_plus_r; mpf_init(u_r_sqaure_plus_r); 
    mpf_t u_r_sqaure_plus_r_plus_one; mpf_init(u_r_sqaure_plus_r_plus_one); 
    mpf_t u_r_times_nine; mpf_init(u_r_times_nine); 
    mpf_t u_total_term; mpf_init(u_total_term);

    // initialising all variables required for computing v
    mpf_t v; mpf_init(v);
    mpf_t v_t_square; mpf_init(v_t_square);
    mpf_t v_u_square; mpf_init(v_u_square);
    mpf_t v_t_times_u; mpf_init(v_t_times_u);
    mpf_t v_adding_sqaures; mpf_init(v_adding_sqaures); 
    
    // initialising all variables required for computing v
    mpf_t w; mpf_init(w);
    mpf_t w_s_square; mpf_init(w_s_square);
    mpf_t w_s_square_plus_s; mpf_init(w_s_square_plus_s);
    mpf_t w_s_square_plus_s_plus_one; mpf_init(w_s_square_plus_s_plus_one);
    mpf_t w_numerator; mpf_init(w_numerator);

    // initialising all variables required for computing a
    mpf_t a_times_w; mpf_init(a_times_w);
    mpf_t a_one_minus_w; mpf_init(a_one_minus_w);
    /* calculate the number term */
    mpir_ui power;
    mpf_t a_total_number; mpf_init(a_total_number);
    mpf_t a_second_term; mpf_init(a_second_term);

    // initialising all variables required for computing s
    mpf_t s_one_minus_r; mpf_init(s_one_minus_r);
    mpf_t s_numerator; mpf_init(s_numerator);
    mpf_t s_u_times_two; mpf_init(s_u_times_two);
    mpf_t s_u_times_two_plus_t; mpf_init(s_u_times_two_plus_t);
    mpf_t s_denominator; mpf_init(s_denominator);

    // initialising all variables required for computing r
    mpf_t r_s_cube; mpf_init(r_s_cube);
    mpf_t r_one_minus_s_cube; mpf_init(r_one_minus_s_cube);

    mpf_t pi; mpf_init(pi);		// Final pi value = (1/a)

    mpir_ui j;					//setting loop variable

    // variables for calculating elapsed time using CHRONO library
    duration<double> elapsed_seconds;
    duration<double> total_elapsed_seconds;

    time_point<system_clock> start;
    time_point<system_clock> end;

    int iter = 1;

    for( j = 0; j < 7; j++, iter++)
    {
        start = system_clock::now();
    	// all calculations for t
    	mpf_mul(t_r_times_two, r, two);
    	mpf_add(t, t_r_times_two, one);
    	
    	// all calculations for u
    	mpf_pow_ui(u_r_sqaure, r, two_ui);
    	mpf_add(u_r_sqaure_plus_r, u_r_sqaure, r);
    	mpf_add(u_r_sqaure_plus_r_plus_one, u_r_sqaure_plus_r, one);
    	mpf_mul(u_r_times_nine, r, nine);
    	mpf_mul(u_total_term, u_r_times_nine, u_r_sqaure_plus_r_plus_one);
    	cube_root(u, u_total_term);

    	// all calculations for v
    	mpf_pow_ui(v_t_square, t, two_ui);
    	mpf_pow_ui(v_u_square, u, two_ui);
    	mpf_mul(v_t_times_u, t, u);
    	mpf_add(v_adding_sqaures, v_t_square, v_u_square);
    	mpf_add(v, v_adding_sqaures, v_t_times_u);

    	// all calculations for w
    	mpf_pow_ui(w_s_square, s, two_ui);
    	mpf_add(w_s_square_plus_s, w_s_square, s);
    	mpf_add(w_s_square_plus_s_plus_one, w_s_square_plus_s, one);
    	mpf_mul(w_numerator, w_s_square_plus_s_plus_one, twenty_seven);
    	mpf_div(w, w_numerator, v);


    	// all calculations for a
    	mpf_mul(a_times_w, w, a);
    	mpf_sub(a_one_minus_w, one, w);
    	if(j == 0)
    	{
    		mpf_set(a_total_number, a);
    	}
 	   	else
    	{	
    		power = (two_ui*j) - one_ui;
	    	mpf_pow_ui(a_total_number, three, power);
    	}       
    	mpf_mul(a_second_term, a_total_number, a_one_minus_w);
    	mpf_add(a, a_times_w, a_second_term);

    	// all calculations for s
    	mpf_sub(s_one_minus_r, one, r);
    	mpf_pow_ui(s_numerator, s_one_minus_r, three_ui);
    	mpf_mul(s_u_times_two, u, two);
    	mpf_add(s_u_times_two_plus_t, s_u_times_two, t);
    	mpf_mul(s_denominator, s_u_times_two_plus_t, v);
    	mpf_div(s, s_numerator, s_denominator);

    	// all calculations for r
    	mpf_pow_ui(r_s_cube, s, three_ui);
    	mpf_sub(r_one_minus_s_cube, one, r_s_cube);
        cube_root(r, r_one_minus_s_cube);
    	
        
        end = system_clock::now();
        elapsed_seconds = end - start;
        
        cout << "elapsed time for iteration " << iter << ": " << elapsed_seconds.count() << "s" << endl;
        
        total_elapsed_seconds+= elapsed_seconds;
    }
    
    cout << "total elapsed time : " << total_elapsed_seconds.count() << "s" << endl;
    mpf_div(pi, one, a);
    print(pi);
    
    return 0;
}

void cube_root(mpf_t& x, const mpf_t a)
{
    /***** Halley's method *****/

	mpf_set_default_prec(BIT_COUNT*PRECISION);  // precision in bits
	mpf_t x_old; mpf_init(x_old); // initialising and setting x_old for comparison 
                                 
    mpf_t x_cube; mpf_init(x_cube);
    mpf_t x_cube_times_two; mpf_init(x_cube_times_two);
    mpf_t a_times_two; mpf_init(a_times_two);
    mpf_t numerator; mpf_init(numerator);
    mpf_t denominator; mpf_init(denominator);
    mpf_t x_bracket_term; mpf_init(x_bracket_term);

    mpf_t exponent; mpf_init_set_d(exponent, 2.718); //initialising the value of exponent to calculate x0

	mpir_ui two_ui = 2;				// setting value two for later computation
	mpir_ui three_ui = 3;				// setting value three for later computation
	
    mpf_t two; mpf_init_set_d(two, 2.0);
    mpf_t three; mpf_init_set_d(three, 3.0);

	mpf_div(x,exponent,three); 			// Initialising the value of x to exponent/3. 

	mpir_ui i;						// Initialising loop variable

    
    for (i = 0; i < MAX_ITERATIONS ; i++)
    {
    	//setting the value of last iteration to old value
    	mpf_set(x_old,x);

    	mpf_pow_ui(x_cube, x, three_ui);
        mpf_mul(x_cube_times_two, x_cube, two);
        mpf_mul(a_times_two, a, two);
        mpf_add(numerator, x_cube, a_times_two);
        mpf_add(denominator, x_cube_times_two, a);
        mpf_div(x_bracket_term, numerator, denominator);
        mpf_mul(x, x_bracket_term, x);
    	
        // do mpf_cmp between x_old and x and see if its equal to 0
    	// if so return
    	if ( mpf_cmp(x,x_old) == 0  )
    	{
    		return;
    	}
    }
}


void print
(
    const mpf_t pi
)
{
    char* digit_ptr = NULL;
    mp_exp_t exp_ptr;
    char* str;
    str = mpf_get_str(digit_ptr, &exp_ptr, BASE, PRECISION, pi);

    char* s = str + 1;          // setting variable to first decimal place
    cout << *str << ".";        //printing "3."
    
    int control_block = 0;       //control variable for block size
    int control_line = 0;       //control variable for line count
    int control_group = 0;       //control variable for group size
    for(int i = 0; i < PLACES; i++)
    {
        if (control_block == BLOCK_SIZE)
        {
            cout << " ";
            control_block = 0;
            control_line++;     //increasing blocks in line 
        }
        if(control_line == LINE_COUNT)
        {
            cout << endl;
            cout << "  ";
            control_line = 0;
            control_group++;    //increasing line in a group
        }
        if (control_group == GROUP_SIZE)
        {
            cout << endl;
            cout << "  ";
            control_group = 0;  //resetting group size for next 500 digits
        }
        
        cout << s[i];      // printing each decimal value
        control_block++;
    }
    cout << endl;
}