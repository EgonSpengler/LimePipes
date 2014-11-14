%{
#define YYPARSE_PARAM scanner
#define YYLEX_PARAM scanner

#include <QDebug>

void yyerror (char const *s);
#include <parser/bwwguidofactory.h>


namespace BwwParser {

BwwGuidoFactory guidoFactory;

}
%}

%code provides {

void clearBwwFactory();
QString getGuidoCode();
void setFlexBufferFromString(const QString &text);

int  yylex (YYSTYPE*, YYLTYPE*);
}

%locations
%pure-parser

%union {
    char *	text;
    int		ival;
}

%token T_TITLE T_TYPE T_COMPOSER T_FOOTER T_INLINE T_FIXED
%token <text> T_COMMENT T_TEMPO
%token <text> LINE_START LINE_END GCLEF START_PART START_PART_REPEAT END_PART END_PART_REPEAT BARLINE BARLINE_TERM
%token <text> MELODY_NOTE TIME_SIG SHARP FLAT NATURAL REST DOT DOT_DBL FERMAT
%token <text> SINGLE_GRACE DOUBLING_REG DOUBLING_HALF DOUBLING_THUMB
%token <text> STRIKE STRIKE_G STRIKE_THUMB STRIKE_HALF
%token <text> STRIKE_DBL STRIKE_DBL_G STRIKE_DBL_THUMB STRIKE_DBL_HALF
%token <text> STRIKE_TRPL STRIKE_TRPL_G STRIKE_TRPL_THUMB STRIKE_TRPL_HALF
%token GRIP GRIP_HALF GRIP_B
%token <text>  GRIP_G GRIP_THUMB GRIP_LONG
%token TAOR TAOR_B TAOR_HALF
%token BUBBLY BUBBLY_HALF
%token BIRL BIRL_LONG BIRL_G BIRL_THUMB
%token THROWD THROWD_HALF THROWD_HVY THROWD_HVY_HALF
%token <text> SHAKE SHAKE_THUMB SHAKE_HALF
%token <text> SLURD SLURE SLURF SLURHG SLURHA
%token TIE_START TIE_END
%token DUPLET_START DUPLET_END TRIPLET_START TRIPLET_END QUADRUPLET3_START QUADRUPLET3_END
%token QUADRUPLET6_START QUADRUPLET6_END QUINTUPLET3_START QUINTUPLET3_END QUINTUPLET4_START QUINTUPLET4_END
%token SEXTUPLET4_START SEXTUPLET4_END SEPTUPLET4_START SEPTUPLET4_END SEPTUPLET6_START SEPTUPLET6_END
%token <text> NO_SYMBOL

%start tune

%%

tune: 	/* empty */
    | tune header_line music_line
    ;

header_line:	/* empty */
        | header_line T_COMMENT			{ qDebug() << QString("p-Comment: %1").arg($2); }
        | header_line T_TEMPO			{ qDebug() << QString("p-TuneTempo: %1").arg($2); }
        | header_line T_COMMENT T_TITLE		{ BwwParser::guidoFactory.setTitle($2); }
        | header_line T_COMMENT T_TYPE		{ qDebug() << QString("p-Type: %1").arg($2); }
        | header_line T_COMMENT T_COMPOSER	{ qDebug() << QString("p-Composer: %1").arg($2); }
        | header_line T_COMMENT T_FOOTER	{ qDebug() << QString("p-Footer: %1").arg($2); }
        | header_line T_COMMENT T_INLINE	{ qDebug() << QString("p-Inline: %1").arg($2); }
        | header_line T_COMMENT T_FIXED		{ qDebug() << QString("p-Fixed: %1").arg($2); }
        | error
        ;


m_symbols: 	/* empty */
         | m_symbols header_line       { qDebug() << QString("p-header line"); }
         | m_symbols GCLEF             { qDebug() << QString("p-gclef: %1\n").arg($2);}
         | m_symbols START_PART        { qDebug() << QString("p-start part: %1\n").arg($2);}
         | m_symbols START_PART_REPEAT { qDebug() << QString("p-end part: %1\n").arg($2);}
         | m_symbols BARLINE           { BwwParser::guidoFactory.addBarline();}
         | m_symbols MELODY_NOTE       { BwwParser::guidoFactory.addMelodyNote($2);}
         | m_symbols TIME_SIG          { qDebug() << QString("p-timesig: %1\n").arg($2); }
         | m_symbols SHARP             { qDebug() << QString("p-sharp: %1\n").arg($2); }
         | m_symbols FLAT
         | m_symbols NATURAL
         | m_symbols REST
         | m_symbols DOT               { BwwParser::guidoFactory.addMelodyNoteDots(1); }
         | m_symbols DOT_DBL           { BwwParser::guidoFactory.addMelodyNoteDots(2); }
         | m_symbols FERMAT
         | m_symbols SINGLE_GRACE
         | m_symbols DOUBLING_REG
         | m_symbols DOUBLING_HALF
         | m_symbols DOUBLING_THUMB
         | m_symbols STRIKE
         | m_symbols STRIKE_G
         | m_symbols STRIKE_THUMB
         | m_symbols STRIKE_HALF
         | m_symbols STRIKE_DBL
         | m_symbols STRIKE_DBL_G
         | m_symbols STRIKE_DBL_THUMB
         | m_symbols STRIKE_DBL_HALF
         | m_symbols STRIKE_TRPL
         | m_symbols STRIKE_TRPL_G
         | m_symbols STRIKE_TRPL_THUMB
         | m_symbols STRIKE_TRPL_HALF
         | m_symbols GRIP
         | m_symbols GRIP_HALF
         | m_symbols GRIP_B
         | m_symbols GRIP_G
         | m_symbols GRIP_THUMB
         | m_symbols GRIP_LONG
         | m_symbols TAOR
         | m_symbols TAOR_B
         | m_symbols TAOR_HALF
         | m_symbols BUBBLY
         | m_symbols BUBBLY_HALF
         | m_symbols BIRL
         | m_symbols BIRL_LONG
         | m_symbols BIRL_G
         | m_symbols BIRL_THUMB
         | m_symbols THROWD
         | m_symbols THROWD_HALF
         | m_symbols THROWD_HVY
         | m_symbols THROWD_HVY_HALF
         | m_symbols SHAKE
         | m_symbols SHAKE_THUMB
         | m_symbols SHAKE_HALF
         | m_symbols SLURD
         | m_symbols SLURE
         | m_symbols SLURF
         | m_symbols SLURHG
         | m_symbols SLURHA
         | m_symbols TIE_START
         | m_symbols TIE_END
         | m_symbols DUPLET_START
         | m_symbols DUPLET_END
         | m_symbols TRIPLET_START
         | m_symbols TRIPLET_END
         | m_symbols QUADRUPLET3_START
         | m_symbols QUADRUPLET3_END
         | m_symbols QUADRUPLET6_START
         | m_symbols QUADRUPLET6_END
         | m_symbols QUINTUPLET3_START
         | m_symbols QUINTUPLET3_END
         | m_symbols QUINTUPLET4_START
         | m_symbols QUINTUPLET4_END
         | m_symbols SEXTUPLET4_START
         | m_symbols SEXTUPLET4_END
         | m_symbols SEPTUPLET4_START
         | m_symbols SEPTUPLET4_END
         | m_symbols SEPTUPLET6_START
         | m_symbols SEPTUPLET6_END
         | m_symbols NO_SYMBOL
         ;


music_line: LINE_START m_symbols LINE_END           { qDebug() << QString("p-Music-line"); }
          | LINE_START m_symbols END_PART           { BwwParser::guidoFactory.endPart(false); }
          | LINE_START m_symbols END_PART_REPEAT    { BwwParser::guidoFactory.endPart(true);  }
          ;
%%

void yyerror (char const *s) {
   qDebug() << QString("Parser Error: %1\n").arg(s);
}

void clearBwwFactory() {
  BwwParser::guidoFactory.clear();
}

QString getGuidoCode() {
  return BwwParser::guidoFactory.getGuidoCode();
}
