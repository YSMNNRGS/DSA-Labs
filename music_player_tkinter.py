import customtkinter as ctk
from tkinter import filedialog
from PIL import Image, ImageTk
import pygame
import os

pygame.mixer.init()
ctk.set_appearance_mode("dark")
ctk.set_default_color_theme("blue")

class MusicPlayer:
    def __init__(self, root):
        self.root = root
        self.root.title("Modern Music Player")
        self.root.geometry("1280x720")
        self.root.resizable(False, False)

        self.playing = False
        self.current_song_index = -1
        self.playlist = []

        self.album_image = Image.open("placeholder.png")
        self.album_photo = ImageTk.PhotoImage(self.album_image)

        self.album_label = ctk.CTkLabel(root, image=self.album_photo, text="")
        self.album_label.pack(pady=10)

        # Controls
        controls_frame = ctk.CTkFrame(root, fg_color="transparent")
        controls_frame.pack(pady=20)

        self.prev_button = ctk.CTkButton(controls_frame, text="⏮ Prev", corner_radius=20, width=100, command=self.play_prev)
        self.prev_button.grid(row=0, column=0, padx=10)

        self.play_button = ctk.CTkButton(controls_frame, text="▶ Play", corner_radius=20, width=100, command=self.toggle_play)
        self.play_button.grid(row=0, column=1, padx=10)

        self.pause_button = ctk.CTkButton(controls_frame, text="⏸ Pause", corner_radius=20, width=100, command=self.pause)
        self.pause_button.grid(row=0, column=2, padx=10)

        self.next_button = ctk.CTkButton(controls_frame, text="⏭ Next", corner_radius=20, width=100, command=self.play_next)
        self.next_button.grid(row=0, column=3, padx=10)

        self.add_button = ctk.CTkButton(controls_frame, text="📁 Add Songs", corner_radius=20, width=130, command=self.add_songs)
        self.add_button.grid(row=0, column=4, padx=10)

        # Vertical Volume Control (Right Side)
        volume_frame = ctk.CTkFrame(root, fg_color="transparent")
        volume_frame.place(relx=0.95, rely=0.4, anchor="center")

        ctk.CTkLabel(volume_frame, text="🔊", font=("Arial", 20)).pack()
        self.volume_slider = ctk.CTkSlider(volume_frame, from_=1, to=0, orientation="vertical", height=200, command=self.set_volume)
        self.volume_slider.set(0.5)
        pygame.mixer.music.set_volume(0.5)
        self.volume_slider.pack(pady=10)

        # Song title label
        self.song_label = ctk.CTkLabel(root, text="No song loaded", font=("Times New Roman", 18))
        self.song_label.pack(pady=10)

    def add_songs(self):
        files = filedialog.askopenfilenames(filetypes=[("MP3 Files", "*.mp3")])
        if files:
            self.playlist.extend(files)
            if self.current_song_index == -1:
                self.current_song_index = 0
                self.play_music()

    def play_music(self):
        if self.playlist:
            song = self.playlist[self.current_song_index]
            pygame.mixer.music.load(song)
            pygame.mixer.music.play()
            self.song_label.configure(text=os.path.basename(song))
            self.playing = True
            self.play_button.configure(text="⏹ Stop")

    def toggle_play(self):
        if not self.playlist:
            return

        if not self.playing:
            self.play_music()
        else:
            pygame.mixer.music.stop()
            self.song_label.configure(text="Stopped")
            self.playing = False
            self.play_button.configure(text="▶ Play")

    def pause(self):
        if self.playing:
            pygame.mixer.music.pause()
            self.playing = False
            self.play_button.configure(text="▶ Resume")
        else:
            pygame.mixer.music.unpause()
            self.playing = True
            self.play_button.configure(text="⏹ Stop")

    def play_next(self):
        if self.playlist:
            self.current_song_index = (self.current_song_index + 1) % len(self.playlist)
            self.play_music()

    def play_prev(self):
        if self.playlist:
            self.current_song_index = (self.current_song_index - 1) % len(self.playlist)
            self.play_music()

    def set_volume(self, value):
        pygame.mixer.music.set_volume(float(value))

# Launch the App
if __name__ == "__main__":
    root = ctk.CTk()
    app = MusicPlayer(root)
    root.mainloop()
