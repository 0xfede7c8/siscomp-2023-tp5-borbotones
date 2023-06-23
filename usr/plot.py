#!/usr/bin/env python3

import matplotlib.pyplot as plt
import numpy as np
import threading
import os


class PinAccess:
    DIR = '/sys/class/gpio'

    def open_files(self):
        files = []
        for pin in self.PINES:
            fullpath = os.path.join(self.DIR, pin, 'value')
            files.append(open(fullpath, 'r'))

        return files

    @staticmethod
    def get_pin_value(file):
        return int(file.read())
    
    def get_value(self):
        full_value = 0
        files = self.open_files()
        for index, file in enumerate(files):
            full_value += (2**index) * self.get_pin_value(file)
            file.close()
        return full_value

    def close(self):
        for file in self.files:
            file.close()

        self.files = []


class Pote(PinAccess):
    PINES = ['gpio14', 'gpio15', 'gpio18', 'gpio23', 'gpio24', 'gpio25', 'gpio8', 'gpio7']



class Distancia(PinAccess):
    PINES = ['gpio2', 'gpio3', 'gpio4', 'gpio17', 'gpio27', 'gpio22', 'gpio10', 'gpio9']
    




def main():
    distancia = Distancia()
    pote = Pote()

    x = []
    y_distancia = []
    y_pote = []

    counter = 0

    plt.show()
    while True:
        x.append(counter)
        y_pote.append(pote.get_value())
        y_distancia.append(distancia.get_value())
        counter += 1

        plt.figure(2)
        plt.plot(x, y_pote, 'b-')
        plt.xlabel('Time (s)')
        plt.ylabel('Valor')
        plt.title('Potenciometro')
        plt.grid(True)
        plt.xlim(max(0, counter - 10), counter + 1)  # Limit x-axis to show the last 10 seconds
        plt.ylim(0, 255)  # Limit y-axis from 0 to 255
        plt.draw()
        plt.pause(1)  # Pause for 1 second
        

        plt.figure(1)
        plt.plot(x, y_distancia, 'b-')
        plt.xlabel('Time (s)')
        plt.ylabel('Valor')
        plt.title('Distancia')
        plt.grid(True)
        plt.xlim(max(0, counter - 10), counter + 1)  # Limit x-axis to show the last 10 seconds
        plt.ylim(0, 30)  # Limit y-axis from 0 to 255
        plt.draw()
        plt.pause(1)  # Pause for 1 second


if __name__ == '__main__':
    main()