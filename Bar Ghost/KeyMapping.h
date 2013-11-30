//
//  KeyMapping.h
//  Bar Ghost
//
//  Created by William Lindmeier on 11/23/13.
//  Copyright (c) 2013 William Lindmeier. All rights reserved.
//

#pragma once

const static NSDictionary *KeyMapping = NULL;
NSString * ImageNameForKey(NSString *keyChar)
{
    if (KeyMapping == NULL)
    {
        KeyMapping = @{
            @"" : @"_BLANK",
            @"0" : @"0.png",
            @"1" : @"1.png",
            @"2" : @"2.png",
            @"3" : @"3.png",
            @"4" : @"4.png",
            @"5" : @"5.png",
            @"6" : @"6.png",
            @"7" : @"7.png",
            @"8" : @"8.png",
            @"9" : @"9.png",
            @"A" : @"A.png",
            @"B" : @"B.png",
            @"C" : @"C.png",
            @"D" : @"D.png",
            @"E" : @"E.png",
            @"F" : @"F.png",
            @"G" : @"G.png",
            @"H" : @"H.png",
            @"I" : @"I.png",
            @"J" : @"J.png",
            @"K" : @"K.png",
            @"L" : @"L.png",
            @"M" : @"M.png",
            @"N" : @"N.png",
            @"O" : @"O.png",
            @"P" : @"P.png",
            @"Q" : @"Q.png",
            @"R" : @"R.png",
            @"S" : @"S.png",
            @"T" : @"T.png",
            @"U" : @"U.png",
            @"V" : @"V.png",
            @"W" : @"W.png",
            @"X" : @"X.png",
            @"Y" : @"Y.png",
            @"Z" : @"Z.png",
            @"&" : @"_AMPERSAND.png",
            @"'" : @"_APOSTROPHE.png",
            @"*" : @"_ASTERISK.png",
            @"@" : @"_AT.png",
            @"\\" : @"_BACKSLASH.png",
            @"]" : @"_BRACKETCLOSE.png",
            @"[" : @"_BRACKETOPEN.png",
            @"•" : @"_BULLET.png",
            @"^" : @"_CARROT.png",
            @":" : @"_COLON.png",
            @"," : @"_COMMA.png",
            @"}" : @"_CURLYCLOSE.png",
            @"{" : @"_CURLYOPEN.png",
            @"$" : @"_DOLLAR.png",
            @"=" : @"_EQUALS.png",
            @"€" : @"_EURO.png",
            @"!" : @"_EXCLAIMATIONMARK.png",
            @"/" : @"_FORWARDSLASH.png",
            @">" : @"_GT.png",
            @"-" : @"_HYPHEN.png",
            @"<" : @"_LT.png",
            @"#" : @"_NUMBER.png",
            @"%" : @"_PERCENT.png",
            @")" : @"_PERENSCLOSE.png",
            @"(" : @"_PERENSOPEN.png",
            @"." : @"_PERIOD.png",
            @"|" : @"_PIPE.png",
            @"+" : @"_PLUS.png",
            @"£" : @"_POUND.png",
            @"?" : @"_QUESTIONMARK.png",
            @"\"" : @"_QUOTATIONMARK.png",
            @"\n" : @"_RETURN.png",
            @";" : @"_SEMICOLON.png",
            @" " : @"_SPACE.png",
            @"~" : @"_TILDE.png",
            @"_" : @"_UNDERSCORE.png",
            @"¥" : @"_YEN.png"
        };
    }
    return KeyMapping[[keyChar uppercaseString]];
}