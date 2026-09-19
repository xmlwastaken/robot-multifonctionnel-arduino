# 🤖 Robot Multifonctionnel Arduino — Voiture Bluetooth avec Évitement d'Obstacles | Bluetooth Obstacle Avoiding Car

> 🇫🇷 Français en premier | 🇬🇧 English below — README bilingue / Bilingual README

---

## 🇫🇷 Français

Projet de Fin d'Année (PFA) 2024-2025 — **Robot mobile multifonctionnel basé sur Arduino UNO** avec commande Bluetooth et détection d'obstacles.

Voiture 4WD télécommandée via module **HC-05** depuis un smartphone, avec système d'évitement d'obstacles automatique grâce à un capteur **HC-SR04**. Deux modes de fonctionnement : manuel (Bluetooth) et autonome (évitement).

### ⚙️ Matériel

| Composant | Modèle | Rôle / Justification |
|---|---|---|
| Carte Arduino | UNO (ATmega328P) | Cœur du système, 16 MHz, 32Ko Flash |
| Module Bluetooth | HC-05 | Commande sans fil, mode maître/esclave |
| Capteur ultrason | HC-SR04 | Détection d'obstacles, bon qualité/prix |
| Driver moteurs | L298N | Contrôle 4 moteurs DC |
| Moteurs | TT DC + roues | 4WD, faible coût |
| Servomoteur | SG90 | Support capteur ultrason (optionnel) |
| Batterie | Li-ion 18650 | Haute capacité, rechargeable |
| Châssis | 4WD | Stabilité |

### 🔌 Câblage Arduino UNO

| Composant | Pin Arduino | Notes |
|---|---|---|
| HC-05 TX | D0 (RX) | Communication série Bluetooth |
| HC-05 RX | D1 (TX) | Utiliser diviseur de tension 5V→3.3V |
| HC-SR04 TRIG | D9 | Signal trigger |
| HC-SR04 ECHO | D8 | Mesure distance |
| L298N IN1 | D2 | Direction moteur A |
| L298N IN2 | D3 | Direction moteur A |
| L298N IN3 | D4 | Direction moteur B |
| L298N IN4 | D5 | Direction moteur B |
| L298N ENA | D10 (PWM) | Vitesse moteur gauche |
| L298N ENB | D11 (PWM) | Vitesse moteur droit |

### 🎮 Commandes Bluetooth

| Envoyer | Action |
|---|---|
| `F` | Avancer |
| `B` | Reculer |
| `L` | Tourner à gauche |
| `R` | Tourner à droite |
| `S` | Stop |

En mode auto (aucune commande reçue), le robot avance et s'arrête si un obstacle est détecté à moins de **20 cm**.

### 🗂️ Structure du dépôt

```
bluetooth-obstacle-car/
├── Arduino/
│   └── bluetooth_obstacle_car.ino   # Code principal (extrait de Bluetooth Obstacle Avoiding Car.docx)
├── Proteus/
│   ├── robot_car.pdsprj             # Simulation Proteus 8 (self-contained)
│   └── Libraries/                   # Librairies Proteus nécessaires
│       ├── ArduinoUNO2TEP.IDX/.LIB
│       ├── BluetoothTEP.IDX/.LIB
│       ├── L298MotorDriverTEP.IDX/.LIB
│       └── UltrasonicTEP.IDX/.LIB + .HEX
└── README.md
```

> ⚠️ **Note importante Proteus:**
> Le fichier original contenait un chemin absolu `X:\XML\Desktop\sketch_apr6a\...\.hex` qui ne fonctionne que sur le PC d'origine.
> Après ouverture de `robot_car.pdsprj`, double-cliquez sur l'Arduino UNO → **Program File** → sélectionnez le `.hex` compilé depuis Arduino IDE (`Arduino IDE → Sketch → Export Compiled Binary`).
> Pour que la simulation trouve les composants, copiez les fichiers de `Proteus/Libraries/` vers `C:\Program Files (x86)\Labcenter Electronics\Proteus 8 Professional\DATA\LIBRARY\` (ou `LIBRARY` de votre installation).

### 🚀 Comment exécuter

**1. Arduino IDE**
1. Ouvrir `Arduino/bluetooth_obstacle_car.ino` dans Arduino IDE
2. Sélectionner Carte: **Arduino UNO**, Port COM
3. Téléverser (Upload)
4. Pour Proteus: **Sketch → Export Compiled Binary** → récupère le `.hex` dans `Arduino/build/.../`

**2. Proteus 8**
1. Installer les librairies de `Proteus/Libraries/` si composants manquants (ArduinoUNO2TEP, BluetoothTEP, L298, Ultrasonic)
2. Ouvrir `Proteus/robot_car.pdsprj`
3. Double-clic Arduino → choisir le `.hex` compilé
4. ▶ Run, connecter avec terminal Bluetooth (9600 baud) et envoyer `F`, `B`, `L`, `R`, `S`

### 📚 Fonctionnalités du code

- `readDistance()` : mesure ultrason
- `autoObstacleAvoid()` : stop si obstacle <20cm, sinon avance
- `executeCommand()` : interprète commandes Bluetooth
- `moveForward()`, `moveBackward()`, `turnLeft()`, `turnRight()`, `stopMotors()`

---

## 🇬🇧 English

Final Year Project (PFA) 2024-2025 — **Multifunctional mobile robot based on Arduino UNO** with Bluetooth control and obstacle avoidance.

4WD car controlled via **HC-05** module from a smartphone, with automatic obstacle avoidance using **HC-SR04**. Two modes: Manual (Bluetooth) and Autonomous (avoidance).

### ⚙️ Hardware

| Component | Model | Role |
|---|---|---|
| Arduino board | UNO (ATmega328P) | Main controller, 16MHz, 32KB Flash |
| Bluetooth module | HC-05 | Wireless control |
| Ultrasonic sensor | HC-SR04 | Obstacle detection |
| Motor driver | L298N | 4 DC motors control |
| Motors | TT DC + wheels | 4WD |
| Servo | SG90 | Ultrasonic mount (optional) |
| Battery | Li-ion 18650 | Rechargeable |

### 🔌 Wiring

| Component | Arduino Pin | Notes |
|---|---|---|
| HC-05 TX | D0 (RX) | Bluetooth serial |
| HC-05 RX | D1 (TX) | Use voltage divider 5V→3.3V |
| HC-SR04 TRIG | D9 | Trigger |
| HC-SR04 ECHO | D8 | Echo distance |
| L298N IN1 | D2 | Motor A dir |
| L298N IN2 | D3 | Motor A dir |
| L298N IN3 | D4 | Motor B dir |
| L298N IN4 | D5 | Motor B dir |
| L298N ENA | D10 PWM | Left motor speed |
| L298N ENB | D11 PWM | Right motor speed |

### 🎮 Bluetooth Commands

| Send | Action |
|---|---|
| `F` | Forward |
| `B` | Backward |
| `L` | Left |
| `R` | Right |
| `S` | Stop |

In auto mode (no command), robot moves forward and stops if obstacle < **20 cm**.

### 🗂️ Repository Structure

```
bluetooth-obstacle-car/
├── Arduino/
│   └── bluetooth_obstacle_car.ino
├── Proteus/
│   ├── robot_car.pdsprj
│   └── Libraries/
└── README.md
```

> ⚠️ **Proteus Note:**
> Original project had absolute hex path `X:\XML\Desktop\sketch_apr6a\...`. After opening `robot_car.pdsprj`, double-click Arduino UNO → **Program File** → select compiled `.hex` from Arduino IDE (Sketch → Export Compiled Binary).
> Copy files from `Proteus/Libraries/` to your Proteus `DATA\LIBRARY\` folder if components are missing.

### 🚀 How to Run

**1. Arduino IDE**
1. Open `Arduino/bluetooth_obstacle_car.ino`
2. Select Board: Arduino UNO, COM Port
3. Upload
4. For Proteus: Sketch → Export Compiled Binary → get `.hex`

**2. Proteus 8**
1. Install libraries from `Proteus/Libraries/` if needed
2. Open `Proteus/robot_car.pdsprj`
3. Double-click Arduino → set Program File to your `.hex`
4. ▶ Run, send `F,B,L,R,S` at 9600 baud

---

## 👥 Auteurs / Authors

**LAAMRI Mohamed** — [laamrimohamed01@gmail.com](mailto:laamrimohamed01@gmail.com)
## 📄 Licence / License

Projet éducatif PFA — réutilisation libre.
Educational PFA project — free to reuse.
