#include <iostream>
#include <QTreeWidgetItem>
#include <QTimer>
#include <QDebug>
#include <QMovie>
#include <QTimer>
#include <QAudioFormat>
#include <QFile>

using namespace std;

#include "gamewindow.h"
#include "mainwindow.h"
#include "ui_gamewindow.h"
#include "Enemy.h"

GameWindow::GameWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GameWindow)
{
    ui->setupUi(this);
    createRooms();
    setRoomImage();
    ui->helmet_text->setText("You awake in the toilet. Find people.");
    ui->scene_view->setVisible(true);
    ui->map_view->setFlat(true);
    ui->use_item_butt->setEnabled(false);
    setBattleView(false);
}

GameWindow::~GameWindow()
{
    delete ui;
}

//Takes a button and sets it to the given Pixmap.

void GameWindow::imageSetup(QPushButton* pb, QPixmap* pixmap)
{
    QIcon icon(*pixmap);
    QSize iconSize(pixmap->width(), pixmap->height());
    pb->setIconSize(iconSize);
    pb->setIcon(icon);
    pb->setVisible(true);
}

//Sets the image to that of the current room.

void GameWindow::setMapImage() {
    QPixmap* pixmap;
    if(currentLevel == 1) {
        pixmap = new QPixmap(":/images/map1.png");
    } else if(currentLevel == 2) {
        pixmap = new QPixmap(":/images/map2.png");
    } else {
        pixmap = new QPixmap(":/images/map3.png");
    }

    imageSetup(ui->map_view, pixmap);
}

void GameWindow::setRoomImage()
{
    imageSetup(ui->scene_view, currentRoom->getRoomImage());
}

//Directional button listeners.

void GameWindow::on_north_butt_clicked()
{
    if(currentRoom != Elevator_3 || (currentRoom == Elevator_3 && character->isItemInInventory("Key Card")))
    {
        go("north");
    }
}

void GameWindow::on_east_butt_clicked()
{
    go("east");
}

void GameWindow::on_west_butt_clicked()
{
     go("west");
}

void GameWindow::on_south_butt_clicked()
{
    go("south");
}

void GameWindow::on_up_butt_clicked()
{
    if(currentLevel > 0 && power == true)
    {
        go("up");
        currentLevel--;
    }
}

void GameWindow::on_down_butt_clicked()
{
    if(currentLevel < 3 && power == true)
    {
        go("down");
        currentLevel++;
    }
}

void GameWindow::on_map_butt_clicked(bool checked)
{
    if(checked == true) {
        setMapImage();
    }
    ui->map_view->setVisible(checked);
}

void GameWindow::on_activate_clicked()
{
    if(currentRoom->shortDescription() == "Power Room" && (character->isItemInInventory("Power Cell") || powerCellIn == true))
    {
        if(powerCellIn == false)
        {
           int pos = character->deleteItem("Power Cell");
           delete ui->inventory->topLevelItem(pos);

        }
        MainWindow *p ;
        p = new MainWindow() ; //MainWindow is referring to mainwindow.cpp for the puzzle
        p->openImage(":/images/microchip.png");
        p->show();
        p->getPointer(this);
    }

    if(currentRoom->shortDescription() == "Engines Room" && character->isItemInInventory("Space Wrench"))
    {
        ui->helmet_text->setText("Yes I fixed the engines. Time to get out of here");
        Elevator_1->addEnemy(new Enemy("Space Angler Boss",1500,0,400,200, new QPixmap(":/images/space_angler.png")));
        timeToGo = true ;
        QSound *engineOn = new QSound(":/sound/Sound/engine.wav", this);
        engineOn->play();
    }

    if(currentRoom->shortDescription() == "Cockpit" && timeToGo == true)
    {
        timeToGo = false;
        ui->tab_view->setVisible(false);
        ui->helmet_text->setVisible(false);
        movie = new QMovie(":/images/space.gif");
        ui->gif->setMovie(movie);
        movie->start();

        timer = new QTimer(this) ;
        connect(timer, SIGNAL(timeout()), this,SLOT(finish())) ;
        timer->start(1000);
    }
}

void GameWindow::finish()
{
    movie->stop();
    movie = new QMovie(":/images/CREDITS.gif");
    ui->gif->setMovie(movie);
    movie->start();
    timer->stop();

}

void GameWindow::createRooms() {

        Cockpit = new Room("Cockpit", new QPixmap(":/images/f1_cockpit.png")) ;

        Toilet = new Room("Toilet", new QPixmap(":/images/f1_toilet.png")) ;
            Toilet->addItem(new Item("Cookie", true, false, 200, new QSound(":/sound/Sound/eat.wav", this)));

        Closet = new Room("Closet", new QPixmap(":/images/f1_closet.png")) ;
            Closet->addItem(new Item("Lead Pipe", false, true, 250, new QSound(":/sound/Sound/pipe.wav", this)));

        Hall_1 = new Room("Hall", new QPixmap(":/images/f1_hall.png")) ;
        Power = new Room("Power Room", new QPixmap(":/images/f1_power.png")) ;
        Elevator_1 = new Room("Elevator, Deck 1", new QPixmap(":/images/f1_elevator.png")) ;

        Escape_Pod = new Room("Escape Pod Bridge", new QPixmap(":/images/f1_escape.png")) ;
            Escape_Pod->addItem(new Item("Power Cell", false, false, 1000, new QSound(":/sound/Sound/blank.wav", this)));
            Escape_Pod->addEnemy(new Enemy("Space Shark", 1000, 100.0, 200, 100, new QPixmap(":/images/space_shark.png")));

        Bed_1 = new Room("My bed room", new QPixmap(":/images/f2_room4.png")) ;
            Bed_1->addItem(new Item("Space Wrench", false, false, 0, new QSound(":/sound/Sound.laser.wav", this)));

        Bed_2 = new Room("Bed room", new QPixmap(":/images/f2_room2.png")) ;
        Bed_3 = new Room("Bed room", new QPixmap(":/images/f2_room3.png")) ;
        Bed_4 = new Room("Bed room", new QPixmap(":/images/f2_room1.png")) ;
            Bed_4->addItem(new Item("Key Card", false, false, 0, new QSound(":/sound/Sound/blank.wav")));

        Hall_2 = new Room("Hall", new QPixmap(":/images/f2_hall_2.png")) ;
        Hall_3 = new Room("Hall", new QPixmap(":/images/f2_hall.png")) ;
        Elevator_2 = new Room("Elevator, Deck 2", new QPixmap(":/images/f1_elevator.png")) ;

        Kitchen = new Room("Kitchen", new QPixmap(":/images/f2_kitchen.png"));
            Kitchen->addItem(new Item("Taytos", true, false, 150, new QSound(":/sound/Sound/eat.wav", this)));
            Kitchen->addItem(new Item("Half eaten sandwich", true, false, 300, new QSound(":/sound/Sound/eat.wav", this)));
            Kitchen->addItem(new Item("Bottle of water", true, false, 250, new QSound(":/sound/Sound/drink.wav", this)));
            Kitchen->addEnemy(new Enemy("Space Walrus", 1000, 0, 250, 150, new QPixmap(":/images/space_walrus.png")));

        Weapons = new Room("Weapons Room", new QPixmap(":/images/f3_weapons.png")) ;
            Weapons->addEnemy(new Enemy("Space Manatee", 1000, 100.0, 200, 100, new QPixmap(":/images/space_manatee.png")));
            Weapons->addItem(new Item("Laser Gun",false, true, 600, new QSound(":/sound/Sound/laser.wav", this)));

        Elevator_3 = new Room("Elevator, Deck 3", new QPixmap(":/images/f1_elevator.png")) ;
        Engines = new Room("Engines Room", new QPixmap(":/images/f1_engines.png")) ;
            Engines->addEnemy(new Enemy("Space Dolphin",1000, 100.0, 200, 100, new QPixmap(":/images/space_dolphin.png")));

        //               F,R,B,L,U,D
        Cockpit->setExits(NULL,NULL,Hall_1,NULL,NULL,NULL);
        Toilet->setExits(NULL, Hall_1, NULL, NULL, NULL, NULL);
        Hall_1->setExits(Cockpit, Closet, Power, Toilet, NULL, NULL);
        Closet->setExits(NULL, NULL, NULL, Hall_1, NULL, NULL);
        Power->setExits(Hall_1,NULL,Elevator_1,NULL,NULL,NULL);
        Elevator_1->setExits(Power,NULL,Escape_Pod,NULL,NULL,Elevator_2);
        Escape_Pod->setExits(Elevator_1, NULL, NULL, NULL, NULL, NULL);
        Bed_1->setExits(NULL, Hall_3, NULL, NULL, NULL, NULL);
        Hall_3->setExits(NULL, Bed_2, Hall_2, Bed_1, NULL, NULL);
        Bed_2->setExits(NULL, NULL, NULL, Hall_3, NULL, NULL);
        Bed_3->setExits(NULL, Hall_2, NULL, NULL, NULL, NULL);
        Hall_2->setExits(Hall_3, Bed_4, Elevator_2, Bed_3, NULL, NULL);
        Bed_4->setExits(NULL, NULL, NULL, Hall_2, NULL, NULL);
        Elevator_2->setExits(Hall_2, NULL, Kitchen, NULL, Elevator_1, Elevator_3);
        Kitchen->setExits(Elevator_2, NULL, NULL, NULL, NULL, NULL);
        Weapons->setExits(NULL, NULL, Elevator_3, NULL, NULL, NULL);
        Elevator_3->setExits(Weapons, NULL, Engines, NULL, Elevator_2, NULL);
        Engines->setExits(Elevator_3, NULL, NULL, NULL, NULL, NULL);

            currentRoom = Toilet;
            addItemToWindow();
            currentLevel = 1;
            inBattle = false;
            powerCellIn = false ;
            timeToGo = false ;

            character = new Character("Chad", 800);

            setBars();

            power = false;
}

void GameWindow::setBars()
{
    ui->char_health_bar->setValue(character->getHealth());
    ui->attack_bar->setValue(character->getAttack());
    ui->defence_bar->setValue(character->getDefence());
}

string GameWindow::go(string direction) {
    //Make the direction lowercase
    //transform(direction.begin(), direction.end(), direction.begin(),:: tolower);
    //Move to the next room
    Room* nextRoom = currentRoom->nextRoom(direction);
    if (nextRoom == NULL)
        return("direction null");
    else
    {
        previousRoom = currentRoom;
        currentRoom = nextRoom;
        setRoomImage();
        string description = currentRoom->shortDescription();

        std::string roomDescription = "You're now in the "+ description + ".";

        //performs an enemy scan in the room.

        addItemToWindow();

        if(currentRoom->numberOfEnemys() > 0){
            inBattle = true;
            roomDescription += currentRoom->displayEnemy();
            ui->enemy_bar->setMaximum(currentRoom->enemysInRoom.at(0).maxHealth);
            ui->enemy_bar->setValue(currentRoom->enemysInRoom.at(0).getHealth());

            imageSetup(ui->map_view, currentRoom->enemysInRoom.at(0).getEnemyImage());

            setBattleView(true);
        }
        ui->helmet_text->setText(QString::fromStdString(roomDescription));
        return currentRoom->longDescription();
    }
}

void GameWindow::addItemToWindow()
{
    ui->room_items->clear();
    string name;
    int power;
    int i;
    //Gets the size of the vector from pointer a

    int size = currentRoom->itemsInRoom.size();
    //Ensures the loop doesen't exceed the vector size

    for (i = 0; i < size; i++)
    {
        name = currentRoom->getItemName(i);
        power = currentRoom->getItemPower(i);
        //Gets the name of the item

        QTreeWidgetItem *addItem = new QTreeWidgetItem(0);
        //Creates the item to add to the tree widget

        addItem->setText(0, QString::fromStdString(name));
        addItem->setText(1, QString::number(power));
        //Sets the text of the item

        ui->room_items->addTopLevelItem(addItem);
        //Adds item to the tree widget
    }
}

void GameWindow::on_room_items_doubleClicked(const QModelIndex &index)
{
    int pos = index.row();
    QTreeWidgetItem *takeItem = new QTreeWidgetItem(0);
    takeItem = ui->room_items->takeTopLevelItem(pos);
    ui->inventory->addTopLevelItem(takeItem);

    character->inventory.push_back(currentRoom->itemsInRoom.at(pos));
    currentRoom->itemsInRoom.erase(currentRoom->itemsInRoom.begin() + pos);
}

void GameWindow::setBattleView(bool battleInd)
{
    if(battleInd){
        ui->tab_view->setCurrentIndex(2);
    } else{
        ui->tab_view->setCurrentIndex(0);
    }
    ui->navi->setDisabled(battleInd);
    ui->map_view->setVisible(battleInd);
    ui->enemy_bar->setVisible(battleInd);
    inBattle = battleInd;
}

int GameWindow::battlePhase()
{
    int i = 0;
    string outputMessage;
    if(selectedItem.isEdible())
        {
            i = 1;

            character->setHealth(character->getHealth() + selectedItem.getPower());
            character->inventory.erase(character->inventory.begin() + battleItemPos);
            outputMessage = "The " + selectedItem.getShortDescription() + " restored health.";
        }
    else if(selectedItem.isWeapon())
    {
        double d = currentRoom->enemysInRoom.at(0).getHealth()-((character->getAttack()/1000.0) * selectedItem.getPower());
        currentRoom->enemysInRoom.at(0).setHealth(d);
        currentRoom->enemysInRoom.at(0).setHealth(d);
        if(character->getAttack() < 500){
            outputMessage = "Weak hit!";
        } else {
            outputMessage = "Nice hit!";
        }
        character->setAttack(character->getAttack() - 100);
        selectedItem.weaponSound();

        //when enemy is defeated
        if(currentRoom->enemysInRoom.at(0).getHealth() == 0)
        {
            i = 2;
            ui->helmet_text->setText("Enemy defeated!");
            character->setXP(character->getXP() + currentRoom->enemysInRoom.at(0).getValue());
            currentRoom->enemysInRoom.erase(currentRoom->enemysInRoom.begin());

            setBattleView(false);
        }
    }
    ui->use_item_butt->setEnabled(false);
    if(i != 2 && inBattle){
        enemyTurn(outputMessage);
    } else {
        setBars();
    }
    return i;
}

//This function retreats the player
//to the previous room they occupied before they
//entered the battle

void GameWindow::on_run_butt_clicked()
{
    if(inBattle)
    {
        currentRoom = previousRoom;
        setRoomImage();
        string description = currentRoom->shortDescription();
        std::string runAway = "You ran back to the "+ description + ". Successful retreat.";
        ui->helmet_text->setText(QString::fromStdString(runAway));
        setBattleView(false);

        addItemToWindow();
    }
}

//This function sets the text of the use button
//indicating to the user if the selected item
//is a weapon or food.

void GameWindow::on_inventory_clicked(const QModelIndex &index)
{
    ui->use_item_butt->setEnabled(false);
    battleItemPos = index.row();
    selectedItem = character->getInventoryItem(battleItemPos);

    if(selectedItem.isWeapon() && inBattle)
    {
        ui->use_item_butt->setText("ATTACK");
        ui->use_item_butt->setEnabled(true);
    }
    else if(selectedItem.isEdible())
    {
        ui->use_item_butt->setText("CONSUME");
        ui->use_item_butt->setEnabled(true);
    }
}

//This button controls the use of items during battles.

void GameWindow::on_use_item_butt_clicked()
{
    if(battlePhase() == 1)
    {
        delete ui->inventory->topLevelItem(battleItemPos);
        selectedItem.weaponSound();
    }
}

void GameWindow::on_build_energy_clicked()
{
    if(inBattle){
        character->setAttack(character->getAttack() + 300);
        enemyTurn("Your attack increased by 600AP.");
    }
}

void GameWindow::on_block_butt_clicked()
{
    if(inBattle){
        character->setDefence(character->getDefence() + 600);
        enemyTurn("Your defence increased by 600DP.");
    }
}

//This function decides what move the Enemy will make.

void GameWindow::enemyTurn(string myMove)
{
    int randNo = rand() % 5;

    if(randNo == 0 && currentRoom->enemysInRoom.at(0).getHealth() < 600){
        currentRoom->enemysInRoom.at(0).setHealth(currentRoom->enemysInRoom.at(0).getHealth() + 300);
        myMove += " The enemy healed.";

    } else {

        character->setHealth(character->getHealth() - (currentRoom->enemysInRoom.at(0).getAttack()*((2000 - character->getDefence())/2000.0)));
        character->setDefence(character->getDefence() - 200);
        myMove += " The enemy attacks and does damage!";
    }

    ui->enemy_bar->setValue(currentRoom->enemysInRoom.at(0).getHealth());
    setBars();
    finalOutputMessage = QString::fromStdString(myMove);
    ui->helmet_text->setText(finalOutputMessage);

    if(character->getHealth() == 0)
    {
        gameOver();
    }
}

void GameWindow::gameOver()
{
    setBattleView(false);

    imageSetup(ui->map_view, new QPixmap(":/images/game_over.png"));
    ui->helmet_text->setText("You're dead.");
    ui->tab_view->setDisabled(true);
}
