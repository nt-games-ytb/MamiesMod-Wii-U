/*
** MAMIESMOD PROJECT
** MamiesMod-Wii-U
** File description:
** The app_menu.c
*/

#include <string>
#include <iostream>
#include "mamiesmod_app.h"

bool MamiesModClient = false;
unsigned char *screenBuffer;

void initializeScreen() {
    OSScreenInit();
    unsigned int screenBuffer0Size = OSScreenGetBufferSizeEx(0);
    unsigned int screenBuffer1Size = OSScreenGetBufferSizeEx(1);

    screenBuffer = (unsigned char *) MEM1_alloc(screenBuffer0Size + screenBuffer1Size, 0x40);

    OSScreenSetBufferEx(0, screenBuffer);
    OSScreenSetBufferEx(1, (screenBuffer + screenBuffer0Size));

    OSScreenEnableEx(0, 1);
    OSScreenEnableEx(1, 1);
}

void print_text(int x, int y, const char *text, ...) {
    char text_to_print[100];
    va_list args;
    va_start(args, text);
    vsnprintf(text_to_print, 100, text, args);
    va_end(args);
    //snprintf(text_to_print, 100, text, __VA_ARGS__);
    OSScreenPutFontEx(0, x, y, text_to_print);
    OSScreenPutFontEx(1, x, y, text_to_print);
}

int app_menu(void) {
    #pragma region Init Menu
    //!*******************************************************************
    //!                   Initialize function pointers                   *
    //!*******************************************************************
    //! do OS (for acquire) and sockets first so we got logging
    InitOSFunctionPointers();
    InitSocketFunctionPointers();
    InitFSFunctionPointers();
    InitVPadFunctionPointers();
    InitSysFunctionPointers();

    if (strcasecmp("men.rpx", cosAppXmlInfoStruct.rpx_name) == 0) {
        return EXIT_RELAUNCH_ON_LOAD;
    } else if (strlen(cosAppXmlInfoStruct.rpx_name) > 0 &&
    strcasecmp("ffl_app.rpx", cosAppXmlInfoStruct.rpx_name) != 0) {
        return EXIT_RELAUNCH_ON_LOAD;
    }

    //! *******************************************************************
    //! *                     Setup EABI registers                        *
    //! *******************************************************************
    register int old_sdata_start, old_sdata2_start;
    asm volatile (
        "mr %0, 13\n"
        "mr %1, 2\n"
        "lis 2, __sdata2_start@h\n"
        "ori 2, 2,__sdata2_start@l\n" // Set the Small Data 2 (Read Only) base register.
        "lis 13, __sdata_start@h\n"
        "ori 13, 13, __sdata_start@l\n"// # Set the Small Data (Read\Write) base register.
        : "=r" (old_sdata_start), "=r" (old_sdata2_start)
        );

    //!*******************************************************************
    //!                    Initialize BSS sections                       *
    //!*******************************************************************
    asm volatile (
        "lis 3, __bss_start@h\n"
        "ori 3, 3,__bss_start@l\n"
        "lis 5, __bss_end@h\n"
        "ori 5, 5, __bss_end@l\n"
        "subf 5, 3, 5\n"
        "li 4, 0\n"
        "bl memset\n"
        );

    SetupKernelCallback();
    memoryInitialize();
    VPADInit();
    initializeScreen();
    mount_sd_fat("sd");
    #pragma endregion Init Menu

    int launchMethod;
    s32 vpadError = -1;
    VPADData vpad_data;

    #pragma region Load config
    int settingSelected = 1;
    int settingSelectedMax = 2;
    std::string selectedArrow1 = "-> ";
    std::string selectedArrow2 = "";
    std::string selectedArrow3 = "";

    config_t config;
    default_config(&config);
    read_config(&config);

    std::string languageText;
    std::string versionText;
    std::string regionText;

    //Language :
    if (config.language == 2) {
        languageText = "FRENCH";
    } else if (config.language == 3) {
        languageText = "JAPANESE";
    } else if (config.language == 4) {
        languageText = "GERMAN";
    } else if (config.language == 5) {
        languageText = "SPANISH";
    } else if (config.language == 6) {
        languageText = "ITALIAN";
    } else {
        languageText = "ENGLISH";
    }

    //Version :
    if (config.version == 1) {
        versionText = "CD";
        config.region = 0;
        regionText = "";
        settingSelectedMax = 2;
    } else {
        versionText = "ESHOP";
        if (config.region == 0) {
            config.region = 1;
            regionText = "EUR";
        }
        settingSelectedMax = 3;
    }

    //Region :
    if (config.region == 1) {
        regionText = "EUR";
    } else if (config.region == 2) {
        regionText = "USA";
    } else if (config.region == 3) {
        regionText = "JPN";
    }
    #pragma endregion

    while (true) {
        VPADRead(0, &vpad_data, 1, &vpadError);
        OSScreenClearBufferEx(0, 0);
        OSScreenClearBufferEx(1, 0);
        InitSocketFunctionPointers();

        int battery = ((float)vpad_data.battery / 6.0) * 100;
        int volume = ((float)vpad_data.volume / 252.0) * 100;
        std::string batteryText = std::to_string(battery);
        std::string volumeText = std::to_string(volume);
        std::string informationText = "";

        #pragma region Display Menu
        print_text(15, 0, ("-- MamiesMod Wii U App --"));
        
        if (config.language == 1) { //English
            if (battery == 0) {
                informationText = "            Battery : CHARGING | Volume : " + volumeText + "%%";
            } else if (battery == 100) {
                informationText = "                Battery : " + batteryText + "%% | Volume : " + volumeText + "%%";
            } else {
                informationText = "                 Battery : " + batteryText + "%% | Volume : " + volumeText + "%%";
            }

            print_text(7, 1, "Your Wii U's IP address : %i.%i.%i.%i", (hostIpAddress >> 24) & 0xFF, (hostIpAddress >> 16) & 0xFF, (hostIpAddress >> 8) & 0xFF, hostIpAddress & 0xFF);
            print_text(-4, 2, (informationText).c_str());

            print_text(-4, 3, "EN :");
            print_text(-4, 4, "If you want to launch the MamiesMod Client press X.");
            print_text(-4, 5, "Otherwise, press A.");
            print_text(-4, 6, "When you are on Minecraft,");
            print_text(-4, 7, "write the IP address of your Wii U on MamiesMod and connect.");

            print_text(-4, 9, "Settings :");
            print_text(-4, 10, ("Language : " + selectedArrow1 + languageText + " | Version : " + selectedArrow2 + versionText + " | Region : " + selectedArrow3 + regionText).c_str());
            print_text(-4, 11, "(Use the buttons on your Wii U to change settings)");

            print_text(-4, 13, "Press HOME to exit...");
            print_text(-4, 15, "MamiesMod Wii U App made by nt games");
            print_text(-4, 16, "with tcpgecko by BullyWiiPlaza and ShineClient by Clover.");
        } else if (config.language == 2) { //French
            if (battery == 0) {
                informationText = "             Batterie : CHARGE | Volume : " + volumeText + "%%";
            } else if (battery == 100) {
                informationText = "               Batterie : " + batteryText + "%% | Volume : " + volumeText + "%%";
            } else {
                informationText = "                Batterie : " + batteryText + "%% | Volume : " + volumeText + "%%";
            }

            print_text(7, 1,  "L'adresse IP de votre Wii U : %i.%i.%i.%i", (hostIpAddress >> 24) & 0xFF, (hostIpAddress >> 16) & 0xFF, (hostIpAddress >> 8) & 0xFF, hostIpAddress & 0xFF);
            print_text(-4, 2, (informationText).c_str());

            print_text(-4, 3, "FR :");
            print_text(-4, 4, "Si vous voulez lancer le MamiesMod Client appuyez sur X.");
            print_text(-4, 5, "Sinon, appuyez sur A");
            print_text(-4, 6, "Lorsque vous serez sur Minecraft,");
            print_text(-4, 7, "ecrivez l'adresse IP de votre Wii U sur MamiesMod et connectez-vous.");

            print_text(-4, 9, "Parametres :");
            print_text(-4, 10, ("Langage : " + selectedArrow1 + languageText + " | Version : " + selectedArrow2 + versionText + " | Region : " + selectedArrow3 + regionText).c_str());
            print_text(-4, 11, "(Utilisez les boutons de votre Wii U pour modifier les parametres)");

            print_text(-4, 13, "Appuyez sur HOME pour quitter...");
            print_text(-4, 15, "MamiesMod Wii U App cree par nt games");
            print_text(-4, 16, "avec tcpgecko par BullyWiiPlaza et ShineClient par Clover.");
        } else if (config.language == 3) { //Japanese
            if (battery == 0) {
                informationText = "               Batteri : JUDEN | Onryo : " + volumeText + "%%";//バッテリー : 充電 | 音量 : " + volumeText + "% ";
            } else if (battery == 100) {
                informationText = "                Batteri : " + batteryText + "%% | Onryo : " + volumeText + "%%";//バッテリー : 0" + batteryText + "% | 音量 : " + volumeText + "% ";
            } else {
                informationText = "                 Batteri : " + batteryText + "%% | Onryo : " + volumeText + "%%";//バッテリー : " + batteryText + "% | 音量 : " + volumeText + "% ";
            }

            print_text(7, 1,  "Wii U no aipiadoresu : %i.%i.%i.%i", (hostIpAddress >> 24) & 0xFF, (hostIpAddress >> 16) & 0xFF, (hostIpAddress >> 8) & 0xFF, hostIpAddress & 0xFF);
            print_text(-4, 2, (informationText).c_str());

            print_text(-4, 3, "JA : (Sorry, the Wii U don't accept japanese characters)");
            print_text(-4, 4, "MamiesMod kuraianto o kido suru baai wa, X o oshimasu.");//"MamiesModクライアントを起動する場合は、Xを押します.")
            print_text(-4, 5, "Sore igai no baai wa, A o oshimasu.");//"それ以外の場合は、Aを押します.")
            print_text(-4, 6, "Minecraft o shiyo shite iru toki wa,");//"Minecraftを使用しているときは、")
            print_text(-4, 7, "Wii U no aipiadoresu o MamiesMod ni kakikonde, setsuzoku shimasu.");//"Wii UのIPアドレスをMamiesModに書き込んで、接続します.")

            print_text(-4, 9, "Settei :");//"設定 :")
            print_text(-4, 10, ("Gengo : " + selectedArrow1 + languageText + " | Bajon : " + selectedArrow2 + versionText + " | Ryoiki : " + selectedArrow3 + regionText).c_str());//("言語 : " + selectedArrow1 + languageText + " | バージョン : " + selectedArrow2 + versionText + " | 領域 : " + selectedArrow3 + regionText).c_str());
            print_text(-4, 11, "(Wii U no botan o shiyo shite settei o henko shimasu)");//"(Wii Uのボタンを使用して設定を変更します)")

            print_text(-4, 13, "HOME o oshite shuryo shimasu...");//"HOMEを押して終了します...")
            print_text(-4, 15, "nt games de tsukura reta MamiesMod Wii U apuri");//"nt games製MamiesMod Wii Uアプリ")
            print_text(-4, 16, "BullyWiiPlaza no tcpgecko to Clover no ShineClient o shiyo shimasu.");//"BullyWiiPlazaのtcpgeckoとCloverのShineClientを使用します.")
        } else if (config.language == 4) { //German
            if (battery == 0) {
                informationText = "           Batterie : AUFLADEN | Volumen : " + volumeText + "%%";
            } else if (battery == 100) {
                informationText = "               Batterie : " + batteryText + "%% | Volumen : " + volumeText + "%%";
            } else {
                informationText = "                Batterie : " + batteryText + "%% | Volumen : " + volumeText + "%%";
            }

            print_text(7, 1, "Die IP-Adresse Ihrer Wii U : %i.%i.%i.%i", (hostIpAddress >> 24) & 0xFF, (hostIpAddress >> 16) & 0xFF, (hostIpAddress >> 8) & 0xFF, hostIpAddress & 0xFF);
            print_text(-4, 2, (informationText).c_str());

            print_text(-4, 3, "DE :");
            print_text(-4, 4, "Wenn Sie den MamiesMod Client starten mochten, drucken Sie X.");
            print_text(-4, 5, "Andernfalls drucken Sie A.");
            print_text(-4, 6, "Wenn Sie auf Minecraft sind,");
            print_text(-4, 7, "Schreiben Sie die IP-Adresse Ihrer Wii U auf MamiesMod und");
            print_text(-4, 8, "verbinden Sie sich.");

            print_text(-4, 9, "Einstellungen :");
            print_text(-4, 10, ("Sprache : " + selectedArrow1 + languageText + " | Ausfuhrung : " + selectedArrow2 + versionText + " | Region : " + selectedArrow3 + regionText).c_str());
            print_text(-4, 11, "(Verwenden Sie die Tasten auf Ihrer Wii U, um Einstellungen");
            print_text(-4, 12, "zu andern)");

            print_text(-4, 13, "Drucken Sie HOME zum Beenden...");
            print_text(-4, 15, "MamiesMod Wii U App von nt games");
            print_text(-4, 16, "mit tcpgecko von BullyWiiPlaza und ShineClient von Clover.");
        } else if (config.language == 5) { //Spanish
            if (battery == 0) {
                informationText = "               Bateria : CARGA | Volumen : " + volumeText + "%%";
            } else if (battery == 100) {
                informationText = "                Bateria : " + batteryText + "%% | Volumen : " + volumeText + "%%";
            } else {
                informationText = "                 Bateria : " + batteryText + "%% | Volumen : " + volumeText + "%%";
            }

            print_text(7, 1,  "La direccion IP de tu Wii U : %i.%i.%i.%i", (hostIpAddress >> 24) & 0xFF, (hostIpAddress >> 16) & 0xFF, (hostIpAddress >> 8) & 0xFF, hostIpAddress & 0xFF);
            print_text(-4, 2, (informationText).c_str());

            print_text(-4, 3, "ES :");
            print_text(-4, 4, "Si quieres lanzar el Cliente MamiesMod pulsa X.");
            print_text(-4, 5, "En caso contrario, pulse A.");
            print_text(-4, 6, "Cuando estes en Minecraft,");
            print_text(-4, 7, "escribe la direccion IP de tu Wii U en MamiesMod y conectate.");

            print_text(-4, 9, "Ajustes :");
            print_text(-4, 10, ("Idioma : " + selectedArrow1 + languageText + " | Version : " + selectedArrow2 + versionText + " | Region : " + selectedArrow3 + regionText).c_str());
            print_text(-4, 11, "(Utiliza los botones de tu Wii U para cambiar la configuracion)");

            print_text(-4, 13, "Pulse HOME para salir...");
            print_text(-4, 15, "MamiesMod Wii U App hecha por nt games");
            print_text(-4, 16, "con tcpgecko de BullyWiiPlaza y ShineClient de Clover.");
        } else if (config.language == 6) { //Italian
            if (battery == 0) {
                informationText = "        Batteria : CARICAMENTO | Volume : " + volumeText + "%%";
            } else if (battery == 100) {
                informationText = "               Batteria : " + batteryText + "%% | Volume : " + volumeText + "%%";
            } else {
                informationText = "                Batteria : " + batteryText + "%% | Volume : " + volumeText + "%%";
            }

            print_text(7, 1, "L'indirizzo IP della Wii U : %i.%i.%i.%i", (hostIpAddress >> 24) & 0xFF, (hostIpAddress >> 16) & 0xFF, (hostIpAddress >> 8) & 0xFF, hostIpAddress & 0xFF);
            print_text(-4, 2, (informationText).c_str());

            print_text(-4, 3, "IT :");
            print_text(-4, 4, "Se si desidera avviare il client MamiesMod, premere X.");
            print_text(-4, 5, "Altrimenti, premere A.");
            print_text(-4, 6, "Quando si e in Minecraft,");
            print_text(-4, 7, "Scrivete l'indirizzo IP della vostra Wii U su MamiesMod");
            print_text(-4, 8, "e collegatevi.");

            print_text(-4, 9, "Impostazioni :");
            print_text(-4, 10, ("Lingua : " + selectedArrow1 + languageText + " | Versione : " + selectedArrow2 + versionText + " | Regione : " + selectedArrow3 + regionText).c_str());
            print_text(-4, 11, "(Usare i pulsanti della Wii U per modificare le impostazioni)");

            print_text(-4, 13, "Premere HOME per uscire...");
            print_text(-4, 15, "MamiesMod App per Wii U realizzata da nt games");
            print_text(-4, 16, "con tcpgecko di BullyWiiPlaza e ShineClient di Clover.");
        }
        #pragma endregion Display Menu

        OSScreenFlipBuffersEx(0);
        OSScreenFlipBuffersEx(1);

        u32 pressedButtons = vpad_data.btns_d | vpad_data.btns_h;

        #pragma region Settings selected
        if (vpad_data.btns_d & (VPAD_BUTTON_RIGHT | VPAD_STICK_L_EMULATION_RIGHT | VPAD_STICK_R_EMULATION_RIGHT | VPAD_BUTTON_R | VPAD_BUTTON_ZR)) {
            settingSelected = settingSelected + 1;
            if (settingSelected == settingSelectedMax + 1) {
                settingSelected = 1;
            }
        }
        else if (vpad_data.btns_d & (VPAD_BUTTON_LEFT | VPAD_STICK_L_EMULATION_LEFT | VPAD_STICK_R_EMULATION_LEFT | VPAD_BUTTON_L | VPAD_BUTTON_ZL)) {
            settingSelected = settingSelected - 1;
            if (settingSelected == 0) {
                settingSelected = settingSelectedMax;
            }
        }
        #pragma endregion

        #pragma region Change settings
        if (settingSelected == 1) { //Language
            selectedArrow1 = "-> ";
            selectedArrow2 = "";
            selectedArrow3 = "";

            if (vpad_data.btns_d & (VPAD_BUTTON_DOWN | VPAD_STICK_L_EMULATION_DOWN | VPAD_STICK_R_EMULATION_DOWN)) {
                config.language = config.language + 1;
                if (config.language == 7) {
                    config.language = 1;
                }
            }
            else if (vpad_data.btns_d & (VPAD_BUTTON_UP | VPAD_STICK_L_EMULATION_UP | VPAD_STICK_R_EMULATION_UP)) {
                config.language = config.language - 1;
                if (config.language == 0) {
                    config.language = 6;
                }
            }

            if (config.language == 1) {
                languageText = "ENGLISH";
            }
            else if (config.language == 2) {
                languageText = "FRENCH";
            }
            else if (config.language == 3) {
                languageText = "JAPANESE";
            }
            else if (config.language == 4) {
                languageText = "GERMAN";
            }
            else if (config.language == 5) {
                languageText = "SPANICH";
            }
            else if (config.language == 6) {
                languageText = "ITALIAN";
            }
        }
        else if (settingSelected == 2) { //Version
            selectedArrow1 = "";
            selectedArrow2 = "-> ";
            selectedArrow3 = "";

            if (vpad_data.btns_d & (VPAD_BUTTON_DOWN | VPAD_STICK_L_EMULATION_DOWN | VPAD_STICK_R_EMULATION_DOWN)) {
                config.version = config.version + 1;
                if (config.version == 3) {
                    config.version = 1;
                }
            }
            else if (vpad_data.btns_d & (VPAD_BUTTON_UP | VPAD_STICK_L_EMULATION_UP | VPAD_STICK_R_EMULATION_UP)) {
                config.version = config.version - 1;
                if (config.version == 0) {
                    config.version = 2;
                }
            }

            if (config.version == 1) {
                versionText = "CD";
                config.region = 0;
                regionText = "";
                settingSelectedMax = 2;
            }
            else if (config.version == 2) {
                versionText = "ESHOP";
                if (config.region == 0) {
                    config.region = 1;
                    regionText = "EUR";
                }
                settingSelectedMax = 3;
            }
        }
        else if (settingSelected == 3) { //Region
            selectedArrow1 = "";
            selectedArrow2 = "";
            selectedArrow3 = "-> ";

            if (vpad_data.btns_d & (VPAD_BUTTON_DOWN | VPAD_STICK_L_EMULATION_DOWN | VPAD_STICK_R_EMULATION_DOWN)) {
                config.region = config.region + 1;
                if (config.region == 4)
                    config.region = 1;
            }
            else if (vpad_data.btns_d & (VPAD_BUTTON_UP | VPAD_STICK_L_EMULATION_UP | VPAD_STICK_R_EMULATION_UP)) {
                config.region = config.region - 1;
                if (config.region == 0)
                    config.region = 3;
            }

            if (config.region == 1) {
                regionText = "EUR";
            } else if (config.region == 2) {
                regionText = "USA";
            } else if (config.region == 3) {
                regionText = "JPN";
            }
        }
        #pragma endregion

        #pragma region Launch
        if (pressedButtons & VPAD_BUTTON_HOME) {
            launchMethod = EXIT;
            break;
        } else if (pressedButtons & VPAD_BUTTON_A) {
            install();
            launchMethod = TCP_GECKO;
            break;
        } else if (pressedButtons & VPAD_BUTTON_X) {
            install();
            launchMethod = TCP_GECKO;
            MamiesModClient = true;
            break;
        }
        #pragma endregion Launch
    }

    write_config(&config);

    asm volatile ("mr 13, %0" : : "r" (old_sdata_start));
    asm volatile ("mr 2,  %0" : : "r" (old_sdata2_start));

    MEM1_free(screenBuffer);
    memoryRelease();

    if (launchMethod == EXIT)
        return EXIT_SUCCESS;
    if (config.version == 1) { //CD
        SYSLaunchMenu();
        return EXIT_SUCCESS;
    }
    if (config.region == 1) { //EUR
        SYSLaunchTitle(0x00050000101D7500);
    } else if (config.region == 2) { //USA
        SYSLaunchTitle(0x00050000101D9D00);
    } else if (config.region == 3) { //JPN
        SYSLaunchTitle(0x00050000101DBE00);
    }
    return EXIT_RELAUNCH_ON_LOAD;
}
