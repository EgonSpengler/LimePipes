%{
#include <QDebug>

#include "parser.hpp"

%}
DIGIT	[0-9]
WS	[ \t\f\r\n]

%option bison-bridge bison-locations noyywrap

    /* Symbol-Condition */
    /* The Start Condition for the music-symbols like Notes, Embellishments, etc.
       because they must be separated by Whitespace.
       The definitions of Tunename and so on don't need any separator. There can be
       skipped over whitespace */
%x SYMBOL

    /* Comment-Condition in Initial-Condition */
%x COMMENT

    /* Comment-Condition in Symbol-Condition */
    /* The comments are slightly different recognized than in initial */
%x COMMENT_SYM

%%

    /******************************************************************
    ***	Defining Start and Stop of Conditions			***
    ******************************************************************/

    /* Start of Symbol-Start-Condition - G Clef */
<INITIAL>&	{
        BEGIN(SYMBOL);
        return(LINE_START);
    }

<INITIAL>\" 	{
        BEGIN(COMMENT);
    }

<COMMENT>[^"]*	{
        yylval->text = strdup(yytext);
        return(T_COMMENT);
    }

    /* Tunetempo-symbol  			*/
<INITIAL,SYMBOL>TuneTempo,{DIGIT}+	{
        yylval->text = strdup(yytext);
        return(T_TEMPO);
    }

    /* everything will be ignored unless not recognized */
<INITIAL>[^ \t\f\r\n"]+	/* eat everything */

<COMMENT>["]	{
        BEGIN(INITIAL);
    }

    /* End Symbol Start-Condition */
<SYMBOL>!I|''!I|!t	{
        BEGIN(INITIAL);
        return(LINE_END);
    }

    /******************************************************************
    ***	Defining Tune-header-symbols				***
    ******************************************************************/
    /* Only In-Line makes sense in SYMBOL-condition, but for compatibility with 	*/
    /* BagpipePlayer all tune-header-symbols are possible in Symbol-condition	*/

    /* mark tunetitle (T)		*/
<INITIAL,SYMBOL>,{WS}*\({WS}*T[^)]+\) {
    //printf( "<- Tune-Title\n" );
    return(T_TITLE);
}
    /* mark tunetype (Y)		*/
<INITIAL,SYMBOL>,{WS}*\({WS}*Y[^)]*\) {
    //printf( "<- Tune-Type\n" );
    return(T_TYPE);
}
    /* mark tunecomposer (M)	*/
<INITIAL,SYMBOL>,{WS}*\({WS}*M[^)]*\) {
    //printf( "<- Tune-Composer\n" );
    return(T_COMPOSER);
}
    /* mark Footer (F)		*/
<INITIAL,SYMBOL>,{WS}*\({WS}*F[^)]*\) {
    //printf( "<- Tune-Footer\n" );
    return(T_FOOTER);
}
    /* mark In-Line (I)		*/
<INITIAL,SYMBOL>,{WS}*\({WS}*I[^)]*\) {
    //printf( "<- Tune-Inline\n" );
    return(T_INLINE);
}
    /* mark Fixed (X)		*/
<INITIAL,SYMBOL>,{WS}*\({WS}*X[^)]*\) {
    //printf( "<- Tune-Fixed\n" );
    return(T_FIXED);
}

    /******************************************************************
    ***	Start of Defining Symbols				***
    ******************************************************************/

    /* G Clef - In the Symbol condition */
<SYMBOL>&	{
            return(GCLEF);
        }

    /* Start of Part */
<SYMBOL>I!	{
            return(START_PART);
        }

    /* Start of Part with repeats */
<SYMBOL>I!''	{
            return(START_PART_REPEAT);
        }

    /* Barline */
<SYMBOL>!	{
            return(BARLINE);
        }


    /* Melody-notes */
<SYMBOL>((?x:LG_1|LA_1|B_1|C_1|D_1|E_1|F_1|HG_1|HA_1|
LG_2|LA_2|B_2|C_2|D_2|E_2|F_2|HG_2|HA_2|
LG_4|LA_4|B_4|C_4|D_4|E_4|F_4|HG_4|HA_4|
LG_8|LA_8|B_8|C_8|D_8|E_8|F_8|HG_8|HA_8|
LG_16|LA_16|B_16|C_16|D_16|E_16|F_16|HG_16|HA_16|
LG_32|LA_32|B_32|C_32|D_32|E_32|F_32|HG_32|HA_32|
LGl_1|LAl_1|Bl_1|Cl_1|Dl_1|El_1|Fl_1|HGl_1|HAl_1|
LGl_2|LAl_2|Bl_2|Cl_2|Dl_2|El_2|Fl_2|HGl_2|HAl_2|
LGl_4|LAl_4|Bl_4|Cl_4|Dl_4|El_4|Fl_4|HGl_4|HAl_4|
LGl_8|LAl_8|Bl_8|Cl_8|Dl_8|El_8|Fl_8|HGl_8|HAl_8|
LGl_16|LAl_16|Bl_16|Cl_16|Dl_16|El_16|Fl_16|HGl_16|HAl_16|
LGl_32|LAl_32|Bl_32|Cl_32|Dl_32|El_32|Fl_32|HGl_32|HAl_32|
LGr_1|LAr_1|Br_1|Cr_1|Dr_1|Er_1|Fr_1|HGr_1|HAr_1|
LGr_2|LAr_2|Br_2|Cr_2|Dr_2|Er_2|Fr_2|HGr_2|HAr_2|
LGr_4|LAr_4|Br_4|Cr_4|Dr_4|Er_4|Fr_4|HGr_4|HAr_4|
LGr_8|LAr_8|Br_8|Cr_8|Dr_8|Er_8|Fr_8|HGr_8|HAr_8|
LGr_16|LAr_16|Br_16|Cr_16|Dr_16|Er_16|Fr_16|HGr_16|HAr_16|
LGr_32|LAr_32|Br_32|Cr_32|Dr_32|Er_32|Fr_32|HGr_32|HAr_32
))	{
        yylval->text = strdup(yytext);
        return(MELODY_NOTE);
    }

    /* time-signatures */
<SYMBOL>((?x:2_2|3_2|2_4|3_4|4_4|5_4|6_4|7_4|C|C_|
2_16|3_16|4_16|5_16|6_16|7_16|8_16|8_16|10_16|11_16|12_16|
2_8|3_8|4_8|5_8|6_8|7_8|8_8|9_8|10_8|11_8|12_8|15_8|18_8|21_8
))	{
        yylval->text = strdup(yytext);
        return(TIME_SIG);
    }

    /* sharps */
<SYMBOL>(sharplg|sharpla|sharpb|sharpc|sharpd|sharpe|sharpf|sharphg|sharpha) {
        yylval->text = strdup(yytext);
        return(SHARP);
    }


    /* flats */
<SYMBOL>(flatlg|flatla|flatb|flatc|flatd|flate|flatf|flathg|flatha) {
        yylval->text = strdup(yytext);
        return(FLAT);
    }

    /* naturals */
<SYMBOL>(naturallg|naturalla|naturalb|naturalc|naturald|naturale|naturalf|naturalhg|naturalha) {
        yylval->text = strdup(yytext);
        return(NATURAL);
    }


    /* Rests */
<SYMBOL>(REST_1|REST_2|REST_4|REST_8|REST_16|REST_32) {
        yylval->text = strdup(yytext);
        return(REST);
    }

    /* Dots */
<SYMBOL>('lg|'la|'b|'c|'d|'e|'f|'hg|'ha) {
        yylval->text = strdup(yytext);
        return(DOT);
    }

    /* Double-Dot */
<SYMBOL>(''lg|''la|''b|''c|''d|''e|''f|''hg|''ha) {
        yylval->text = strdup(yytext);
        return(DOT_DBL);
    }

    /* Fermata */
<SYMBOL>(fermatlg|fermatla|fermatb|fermatc|fermatd|fermate|fermatf|fermathg|fermatha) {
        yylval->text = strdup(yytext);
        return(FERMAT);
    }

    /* single-graces */
<SYMBOL>(ag|bg|cg|dg|eg|fg|gg|tg) {
        yylval->text = strdup(yytext);
        return(SINGLE_GRACE);
    }

    /* Regular Doublings */
<SYMBOL>(dblg|dbla|dbb|dbc|dbd|dbe|dbf|dbhg|dbha) {
        yylval->text = strdup(yytext);
        return( DOUBLING_REG  );
    }

    /* Half Doublings */
<SYMBOL>(hdblg|hdbla|hdbb|hdbc|hdbd|hdbe|hdbf) {
        yylval->text = strdup(yytext);
        return( DOUBLING_HALF  );
    }

    /* Thumb Doublings */
<SYMBOL>(tdblg|tdbla|tdbb|tdbc|tdbd|tdbe|tdbf) {
        yylval->text = strdup(yytext);
        return( DOUBLING_THUMB );
    }

    /* Singlegrace-Strikes */
<SYMBOL>((?x:strlg|strla|strb|strc|strd|stre|strf|strhg /* Like single gracenotes */
)) 	 {
        yylval->text = strdup(yytext);
        return( STRIKE );
    }

    /* G Strikes (Regular) */
<SYMBOL>(gstla|gstb|gstc|gstd|lgstd|gste|gstf) {
        yylval->text = strdup(yytext);
        return( STRIKE_G );
    }

    /* Thumb Strikes */
<SYMBOL>(tstla|tstb|tstc|tstd|ltstd|tste|tstf|tsthg) {
        yylval->text = strdup(yytext);
        return( STRIKE_THUMB );
    }

    /* Half Strikes */
<SYMBOL>(hstla|hstb|hstc|hstd|lhstd|hste|hstf|hsthg) {
        yylval->text = strdup(yytext);
        return( STRIKE_HALF );
    }

    /* Double Strikes (Regular) */
<SYMBOL>(st2la|st2b|st2c|st2d|lst2d|st2e|st2f|st2hg|st2ha) {
        yylval->text = strdup(yytext);
        return( STRIKE_DBL );
    }

    /* G-Double-Strikes */
<SYMBOL>(gst2la|gst2b|gst2c|gst2d|lgst2d|gst2e|gst2f) {
        yylval->text = strdup(yytext);
        return( STRIKE_DBL_G );
    }

    /* Thumb-Double-Strike */
<SYMBOL>(tst2la|tst2b|tst2c|tst2d|ltst2d|tst2e|tst2f|tst2hg) {
        yylval->text = strdup(yytext);
        return( STRIKE_DBL_THUMB );
    }

    /* Half-Double-Strike */
<SYMBOL>(hst2la|hst2b|hst2c|hst2d|lhst2d|hst2e|hst2f|hst2hg|hst2ha) {
        yylval->text = strdup(yytext);
        return( STRIKE_DBL_HALF );
    }

    /* Triple Strikes (Regular) */
<SYMBOL>(st3la|st3b|st3c|st3d|lst3d|st3e|st3f|st3hg|st3ha) {
        yylval->text = strdup(yytext);
        return( STRIKE_TRPL );
    }

    /* G-Triple-Strikes */
<SYMBOL>(gst3la|gst3b|gst3c|gst3d|lgst3d|gst3e|gst3f) {
        yylval->text = strdup(yytext);
        return( STRIKE_TRPL_G );
    }

    /* Thumb-Triple-Strike */
<SYMBOL>(tst3la|tst3b|tst3c|tst3d|ltst3d|tst3e|tst3f|tst3hg) {
        yylval->text = strdup(yytext);
        return( STRIKE_TRPL_THUMB );
    }

    /* Half-Triple-Strike */
<SYMBOL>(hst3la|hst3b|hst3c|hst3d|lhst3d|hst3e|hst3f|hst3hg|hst3ha) {
        yylval->text = strdup(yytext);
        return( STRIKE_TRPL_HALF );
    }

    /* Grips */
<SYMBOL>(grp) {
        yylval->text = strdup(yytext);
        return( GRIP );
    }
<SYMBOL>(hgrp) {
        yylval->text = strdup(yytext);
        return( GRIP_HALF );
    }

<SYMBOL>(grpb) {
        yylval->text = strdup(yytext);
        return( GRIP_B );
    }

    /* G-Grip */
<SYMBOL>(ggrpla|ggrpb|ggrpc|ggrpdb|ggrpd|ggrpe|ggrpf) {
        yylval->text = strdup(yytext);
        return( GRIP_G );
    }
    /* Thumb-Grip */
<SYMBOL>(tgrpla|tgrpb|tgrpc|tgrpdb|tgrpd|tgrpe|tgrpf|tgrphg) {
        yylval->text = strdup(yytext);
        return( GRIP_THUMB );
    }

    /* Long-Grip (Pitch of following note as starting grace)*/
<SYMBOL>(hgrpla|hgrpb|hgrpc|hgrpdb|hgrpd|hgrpe|hgrpf|hgrphg|hgrpha) {
        yylval->text = strdup(yytext);
        return( GRIP_LONG );
    }

    /* Taorluaths */
<SYMBOL>(tar) {
        yylval->text = strdup(yytext);
        return( TAOR );
    }
<SYMBOL>(tarb) {
        yylval->text = strdup(yytext);
        return( TAOR_B);
    }
<SYMBOL>(htar) {
        yylval->text = strdup(yytext);
        return( TAOR_HALF );
    }

    /* Bubblys */
<SYMBOL>(bubly) {
        yylval->text = strdup(yytext);
        return( BUBBLY );
    }

<SYMBOL>(hbubly) {
        yylval->text = strdup(yytext);
        return( BUBBLY_HALF );
    }

    /* Birls */
<SYMBOL>(brl) {
        yylval->text = strdup(yytext);
        return( BIRL );
    }

    /* Long-Birls */
<SYMBOL>(abr) {
        yylval->text = strdup(yytext);
        return( BIRL_LONG );
    }

    /* G-Birls */
<SYMBOL>(gbr) {
        yylval->text = strdup(yytext);
        return( BIRL_G );
    }

    /* Thumb-Birls */
<SYMBOL>(tbr) {
        yylval->text = strdup(yytext);
        return( BIRL_THUMB );
    }

    /* Throw on D */
<SYMBOL>(thrd) {
        yylval->text = strdup(yytext);
        return( THROWD );
    }

<SYMBOL>(hthrd) {
        yylval->text = strdup(yytext);
        return(THROWD_HALF);
    }

    /* Heavy-Throw on D */
<SYMBOL>(hvthrd) {
        yylval->text = strdup(yytext);
        return( THROWD_HVY );
    }

<SYMBOL>(hhvthrd) {
        yylval->text = strdup(yytext);
        return( THROWD_HVY_HALF );
    }

    /* Shakes (aka Peles) */
<SYMBOL>(pella|pelb|pelc|peld|lpeld|pele|pelf) {
        yylval->text = strdup(yytext);
        return( SHAKE );
    }

    /* Thumb-Shakes (aka Peles) */
<SYMBOL>(tpella|tpelb|tpelc|tpeld|ltpeld|tpele|tpelf|tpelhg) {
        yylval->text = strdup(yytext);
        return( SHAKE_THUMB );
    }

    /* Half-Shakes (aka Peles) */
<SYMBOL>(hpella|hpelb|hpelc|hpeld|lhpeld|hpele|hpelf|hpelhg) {
        yylval->text = strdup(yytext);
        return( SHAKE_HALF );
    }

    /* D-Double-Graces (Slurs) */
<SYMBOL>(dlg|dla|db|dc) {
        yylval->text = strdup(yytext);
        return( SLURD );
    }

    /* E-Double-Graces (Slurs) */
<SYMBOL>(elg|ela|eb|ec|ed) {
        yylval->text = strdup(yytext);
        return( SLURE );
    }

    /* F-Double-Graces (Slurs) */
<SYMBOL>(flg|fla|fb|fc|fd|fe) {
        yylval->text = strdup(yytext);
        return( SLURF );
    }

    /* G-Double-Graces (Slurs) */
<SYMBOL>(glg|gla|gb|gc|gd|ge|gf) {
        yylval->text = strdup(yytext);
        return( SLURHG );
    }

    /* Thumb-Double-Graces (Slurs) */
<SYMBOL>(tlg|tla|tb|tc|td|te|tf|thg) {
        yylval->text = strdup(yytext);
        return( SLURHA );
    }

    /* Tie-Start */
<SYMBOL>(\^ts) {
        return( TIE_START );
    }

    /* Tie-End */
<SYMBOL>(\^te) {
        return( TIE_END );
    }

    /* Tie-Old (No End-Sign)*/
    /* returns also an TIE_START because the information, how many
       notes should be tied together should be checked somewhere else */
<SYMBOL>(\^tlg|\^tla|\^tb|\^tc|\^td|\^te|\^tf|\^thg|\^tha) {
        return( TIE_START );
    }

    /* Duplets-Start (2 Notes played in the time of 3)*/
<SYMBOL>(\^2s) {
        return( DUPLET_START );
    }

    /* Duplets-End (2 Notes played in the time of 3)*/
<SYMBOL>(\^2e) {
        return( DUPLET_END );
    }

    /* Triplet-Start (3 Notes played in the time of 2)*/
<SYMBOL>(\^3s) {
        return( TRIPLET_START );
    }

    /* Triplet-End (3 Notes played in the time of 2)*/
<SYMBOL>(\^3e) {
        return( TRIPLET_END );
    }

    /* Quadruplets3-Start (4 Notes played in the time of 3)*/
<SYMBOL>(\^43s) {
        return( QUADRUPLET3_START );
    }

    /* Quadruplets3-End (4 Notes played in the time of 3)*/
<SYMBOL>(\^43e) {
        return( QUADRUPLET3_END );
    }

    /* Quadruplets6-Start (4 Notes played in the time of 6)*/
<SYMBOL>(\^46s) {
        return( QUADRUPLET6_START );
    }

    /* Quadruplets6-End (4 Notes played in the time of 6)*/
<SYMBOL>(\^46e) {
        return( QUADRUPLET6_END );
    }

    /* Quintuplet3-Start (5 Notes played in the time of 3)*/
<SYMBOL>(\^53s) {
        return( QUINTUPLET3_START );
    }

    /* Quintuplet3-End (5 Notes played in the time of 3)*/
<SYMBOL>(\^53e) {
        return( QUINTUPLET3_END );
    }

    /* Quintuplet4-Start (5 Notes played in the time of 4)*/
<SYMBOL>(\^54s) {
        return( QUINTUPLET4_START );
    }

    /* Quintuplet4-End (5 Notes played in the time of 4)*/
<SYMBOL>(\^54e) {
        return( QUINTUPLET4_END );
    }

    /* Sextuplet4-Start (6 Notes played in the time of 4)*/
<SYMBOL>(\^64s) {
        return( SEXTUPLET4_START );
    }

    /* Sextuplet4-End (6 Notes played in the time of 4)*/
<SYMBOL>(\^64e) {
        return( SEXTUPLET4_END );
    }

    /* Septuplet4-Start (7 Notes played in the time of 4)*/
<SYMBOL>(\^74s) {
        return( SEPTUPLET4_START );
    }

    /* Septuplet4-End (7 Notes played in the time of 4)*/
<SYMBOL>(\^74e) {
        return( SEPTUPLET4_END );
    }

    /* Septuplet6-Start (7 Notes played in the time of 6)*/
<SYMBOL>(\^76s) {
        return( SEPTUPLET6_START );
    }

    /* Septuplet6-End (7 Notes played in the time of 6)*/
<SYMBOL>(\^76e) {
        return( SEPTUPLET6_END );
    }

    /* Comments in the Symbol-Condition */
<SYMBOL>\"	{
        BEGIN(COMMENT_SYM);
    }

<COMMENT_SYM>[^\n"]*	{
        yylval->text = strdup(yytext);
        return( T_COMMENT );
    }

<COMMENT_SYM>\"|\n		{
        BEGIN(SYMBOL);
    }

    /* Recognizing all unrecognized symbols */
<SYMBOL>[^ \t\f\r\n"]+	{
        yylval->text = strdup(yytext);
        return( NO_SYMBOL );
    }

    /******************************************************************
    ***	End of Defining Symbols					***
    ******************************************************************/

{WS}+	;	/*Eat up whitespace*/

%%

void setFlexBufferFromString(const QString &text)
{
  YY_BUFFER_STATE bufState;
  bufState = yy_scan_string(text.toUtf8().data());
  yy_switch_to_buffer(bufState);
}
