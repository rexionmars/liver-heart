import tkinter as tk
from tkinter import ttk
import matplotlib.pyplot as plt
from matplotlib.backends.backend_tkagg import FigureCanvasTkAgg
from scipy.interpolate import pchip_interpolate
import random
import threading

# Número máximo de pontos no gráfico
MAX_PONTOS_GRAFICO = 20
MIN_PONTOS_INTERPOLACAO = 2

# Função para atualizar os dados (simulação de sinais vitais)
def atualizar_dados():
    # Simulação de dados de pressão arterial sistólica ao longo do tempo
    pressao_arterial_sistolica = random.randint(100, 160)
    dados_pam.append(pressao_arterial_sistolica)

    # Mantenha o histórico de dados dentro do limite
    if len(dados_pam) > MAX_PONTOS_GRAFICO:
        dados_pam.pop(0)

    # Atualize o rótulo com os dados simulados
    lbl_pam["text"] = "Pressão Arterial Sistólica: " + str(pressao_arterial_sistolica)

    # Atualize o gráfico
    plot_pam()

# Função para criar um temporizador e atualizar os dados automaticamente
def atualizacao_automatica():
    while True:  # Continuar atualizando indefinidamente
        atualizar_dados()
        root.after(1000)  # Atualize a cada 1000 milissegundos (1 segundo)

# Função para atualizar o gráfico de pressão arterial sistólica
def plot_pam():
    # Limpe o gráfico
    ax.clear()

    if len(dados_pam) >= MIN_PONTOS_INTERPOLACAO:
        # Interpolação usando pchip
        x = range(len(dados_pam))
        y = dados_pam
        x_new = [i * 0.1 for i in range((len(dados_pam) - 1) * 10)]
        y_new = pchip_interpolate(x, y, x_new)

        # Atualize o gráfico com os dados interpolados
        ax.plot(x_new, y_new, label="PAM", color="blue", linewidth=2, antialiased=True)
        ax.set_xlabel("Tempo")
        ax.set_ylabel("Pressão Arterial Sistólica")
        ax.legend()

    # Atualize o gráfico na interface gráfica
    canvas.draw()

# Configurações da janela principal
root = tk.Tk()
root.title("Monitor de Sinais Vitais")

# Rótulos para exibir os dados
lbl_pam = tk.Label(root, text="", font=("Helvetica", 12))
lbl_pam.pack()

# Inicialize os dados
dados_pam = []

# Configuração do gráfico
fig, ax = plt.subplots()
ax.set_xlabel("Tempo")
ax.set_ylabel("Pressão Arterial Sistólica")
ax.set_xlim(0, (MAX_PONTOS_GRAFICO - 1) * 10)
canvas = FigureCanvasTkAgg(fig, master=root)
canvas_widget = canvas.get_tk_widget()
canvas_widget.pack()

# Inicie o temporizador para atualizar os dados automaticamente
thread = threading.Thread(target=atualizacao_automatica)
thread.daemon = True  # Para que a thread termine quando a janela é fechada
thread.start()

# Inicie o loop principal da interface gráfica
root.mainloop()
