
class MorseCodeTranslator(object):
    __morse_code = {
        'A':'.-',
        'B':'-...',
        'C':'-.-.',
        'D':'-..',
        'E':'.',
        'F':'..-.',
        'G':'--.',
        'H':'....',
        'I':'..',
        'J':'.---',
        'K':'-.-',
        'L':'.-..',
        'M':'--',
        'N':'-.',
        'O':'---',
        'P':'.--.',
        'Q':'--.-',
        'R':'.-.',
        'S':'...',
        'T':'-',
        'U':'..-',
        'V':'...-',
        'W':'.--',
        'X':'-..-',
        'Y':'-.--',
        'Z':'--..',

        '1':'.----',
        '2':'..---',
        '3':'...--',
        '4':'....-',
        '5':'.....',
        '6':'-....',
        '7':'--...',
        '8':'---..',
        '9':'----.',
        '0':'-----',

        '.':'.-.-.-',
        ',':'--..--',
        '?':'..--..',
        '‘':'.----.',
        '!':'.-.--',
        '/':'-..-.',
        '(':'-.--.',
        ')':'-.--.-',
        '&':'.-...',
        ':':'---...',
        ';':'-.-.-.',
        '=':'-...-',
        '-':'-....-',
        '_':'..--.-',
        '"':'.-..-.',
        '$':'...-..-',
        '@':'.--.-.',
    }

    errorChar = "�"


    @staticmethod
    def getMorseCodeTable():
        return MorseCodeTranslator.__morse_code


    @staticmethod
    def isMorse(text):
        return all( 
            map( lambda char: False if not char in [".","-"," ","/","\n",MorseCodeTranslator.errorChar] else True , text) 
        )


    @staticmethod
    def translate(text):

        new_text = ""

        if MorseCodeTranslator.isMorse(text):

            text = text.split(" ")
            

            for char in text:

                if char == "/":
                    new_text += " "
                    continue
                if char == MorseCodeTranslator.errorChar:
                    if "\n" in char:
                        new_text += "\n"
                    continue
                

                for (key,value) in MorseCodeTranslator.__morse_code.items():

                    if "\n" in char:
                        nextLine_i = char.index("\n")
                    else:
                        nextLine_i = -1

                    if char.replace("\n","") == value:

                        if nextLine_i != -1:
                            if nextLine_i == 0:
                                new_text += "\n" + key
                            else:
                                new_text += key + "\n"
                        else:
                            new_text += key
        else:
            for char in text.upper():
                if char == "\n":
                    new_text += "\n"
                    continue
                elif char.isspace():
                    new_text += "/ "
                    continue
                try:  
                    new_text += MorseCodeTranslator.__morse_code[char] + " "
                except KeyError:
                    new_text += MorseCodeTranslator.errorChar + " "
            if new_text.endswith("/"):
                new_text = new_text[:-2]
        return new_text.strip().capitalize()