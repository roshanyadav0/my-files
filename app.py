
from translator import MorseCodeTranslator
from tkinter import Tk,Label,Text,Frame,Button,Scrollbar,IntVar
import sys

if "win" in sys.platform:
    from winsound import Beep


class App(object):

    __button_width = 15
    __button_height = 1
    __button_bg = "green2"
    __button_fg = "white"
    __button_font = ("Autumn",27)
    __button_relief = "flat"

    __inputText_height = 5

    __label_fg = "#F5F5F5"
    __label_font = ("Impact",20)

    __outputText_height = 7

    __text_width = 50
    __text_bg = "white"
    __text_fg = "black"
    __text_font = ("Arial",14)

    frequency = 1500

    window_title = "Morse Code Translator"
    window_geometry = [600,500]
    window_bg = "gray50"



    def __init__(self):
        self.__root = Tk()
        self.__root.geometry("{}x{}".format(*self.window_geometry))
        self.__root["bg"] = self.window_bg
        self.__root.title(self.window_title)
        self.__root.resizable(False,False)
        self.__root.focus_force()
        self.__root.bind("<Return>",self.translate)

        self.__playing = False
        self.__waitVar = IntVar()
        self.build()



    def build(self):
        Label(
            self.__root,
            bg = self.window_bg,
            font = self.__label_font,
            fg = self.__label_fg,
            text = "Input:",
            pady = 10
            ).pack()
        input_frame = Frame(self.__root,bg=self.window_bg)
        input_frame.pack()
        self.__inputText = Text(
            input_frame,
            width = self.__text_width,
            height = self.__inputText_height,
            bg = self.__text_bg,
            fg= self.__text_fg,
            font = self.__text_font,
            wrap = "word"
            )
        self.__inputText.insert(0.0," Type here...")
        scrollbar = Scrollbar(input_frame)
        scrollbar.pack(side="right",fill="y")
        self.__inputText.config(yscrollcommand=scrollbar.set)
        scrollbar.config(command=self.__inputText.yview)

        self.__inputText.pack()
        Label(
            self.__root,
            bg = self.window_bg,
            font = self.__label_font,
            fg = self.__label_fg,
            text = "Output:",
            pady = 10
            ).pack()
        output_frame = Frame(self.__root,bg=self.window_bg)
        output_frame.pack()

        self.__outputText = Text(
            output_frame,
            width = self.__text_width,
            height = self.__outputText_height,
            bg = self.__text_bg,
            fg= self.__text_fg,
            font = self.__text_font,
            wrap = "word"
            )
        self.__outputText.insert(0.0," The text translation will appear here.")
        scrollbar = Scrollbar(output_frame)
        scrollbar.pack(side="right",fill="y")
        self.__outputText.config(yscrollcommand=scrollbar.set)
        scrollbar.config(command=self.__outputText.yview)

        self.__outputText.pack()
        buttons_frame = Frame(self.__root,bg=self.window_bg,pady=20)
        buttons_frame.pack()

        button1_frame = Frame(buttons_frame,bg="black",padx=2,pady=2)
        button1_frame.pack(side="left")

        self.__button1 = Button(
            button1_frame,
            width = self.__button_width,
            height = self.__button_height,
            relief = self.__button_relief,
            bg = self.__button_bg,
            fg = self.__button_fg,
            font = self.__button_font,
            text = "Translate",
            command = self.translate
        )
        self.__button1.pack()

        if "win" in sys.platform:

            Label(buttons_frame,bg=self.window_bg,padx=5).pack(side="left")

            button2_frame = Frame(buttons_frame,bg="black",padx=2,pady=2)
            button2_frame.pack(side="left")

            self.__button2 = Button(
                button2_frame,
                width = self.__button_width,
                height = self.__button_height,
                relief = self.__button_relief,
                bg = self.__button_bg,
                fg = self.__button_fg,
                font = self.__button_font,
                text = "Play",
                command = self.play
            )
            self.__button2.pack()

        self.__root.mainloop()



    def play(self):
        if self.__playing:
            self.__playing = False
            return

        text = self.__outputText.get(0.0,"end")
        if not text or text.isspace() or not MorseCodeTranslator.isMorse(text): return

        self.__playing = True
        self.__button2.config(text = "Stop")

        for char in text.split(" "):

            for l in char:

                if not self.__playing:
                    break

                if l == MorseCodeTranslator.errorChar:
                    continue

                if l == ".":
                    Beep(self.frequency,300)

                elif l == "-":
                    Beep(self.frequency,600)

                elif l == "/":
                    self.wait(2100)
            
            
            if not self.__playing:
                break

            self.wait(900)

        self.__playing = False
        self.__button2.config(text = "Play")



    def translate(self,event=None):
        
        text = self.__inputText.get(0.0,"end")
        if not text: return
        self.__outputText.delete(0.0,"end")
        self.__outputText.insert(0.0,MorseCodeTranslator.translate(text))



    def wait(self,ms):

        self.__waitVar.set(0)
        self.__root.after(ms,self.__waitVar.set,1)
        self.__root.wait_variable(self.__waitVar)
        self.__waitVar.set(0)



if __name__ == "__main__":
    App()

    