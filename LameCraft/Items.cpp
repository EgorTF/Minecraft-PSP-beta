#include "Items.h"

//items' id begin from 250

WoodenPickaxe::WoodenPickaxe():BaseItem()
{
	textureRow = 9;

	plane = 4;
	durabilityPoints = 60;
}

item_t WoodenPickaxe::getID(){ return 250;}

StonePickaxe::StonePickaxe():BaseItem()
{
	textureRow = 9;

	plane = 3;
	durabilityPoints = 132;
}

item_t StonePickaxe::getID(){ return 251;}

IronPickaxe::IronPickaxe():BaseItem()
{
	textureRow = 9;

	plane = 2;
	durabilityPoints = 251;
}

item_t IronPickaxe::getID(){ return 252;}

DiamondPickaxe::DiamondPickaxe():BaseItem()
{
	textureRow = 9;

	plane = 1;
	durabilityPoints = 1562;
}

item_t DiamondPickaxe::getID(){ return 253;}

GoldenPickaxe::GoldenPickaxe():BaseItem()
{
	textureRow = 9;

	plane = 0;
	durabilityPoints = 33;
}

item_t GoldenPickaxe::getID(){ return 254;}

WoodenSword::WoodenSword():BaseItem()
{
	textureRow = 11;

	plane = 4;
	durabilityPoints = 60;
}

item_t WoodenSword::getID(){ return 255;}

StoneSword::StoneSword():BaseItem()
{
	textureRow = 11;

	plane = 3;
	durabilityPoints = 132;
}

item_t StoneSword::getID(){ return 256;}

IronSword::IronSword():BaseItem()
{
	textureRow = 11;

	plane = 2;
	durabilityPoints = 251;
}

item_t IronSword::getID(){ return 257;}

DiamondSword::DiamondSword():BaseItem()
{
	textureRow = 11;

	plane = 1;
	durabilityPoints = 1562;
}

item_t DiamondSword::getID(){ return 258;}

GoldenSword::GoldenSword():BaseItem()
{
	textureRow = 11;

	plane = 0;
	durabilityPoints = 33;
}

item_t GoldenSword::getID(){ return 259;}

WoodenShovel::WoodenShovel():BaseItem()
{
	textureRow = 10;

	plane = 4;
	durabilityPoints = 60;
}

item_t WoodenShovel::getID(){ return 260;}

StoneShovel::StoneShovel():BaseItem()
{
	textureRow = 10;

	plane = 3;
	durabilityPoints = 132;
}

item_t StoneShovel::getID(){ return 261;}

IronShovel::IronShovel():BaseItem()
{
	textureRow = 10;

	plane = 2;
	durabilityPoints = 251;
}

item_t IronShovel::getID(){ return 262;}

DiamondShovel::DiamondShovel():BaseItem()
{
	textureRow = 10;

	plane = 1;
	durabilityPoints = 1562;
}

item_t DiamondShovel::getID(){ return 263;}

GoldenShovel::GoldenShovel():BaseItem()
{
	textureRow = 10;

	plane = 0;
	durabilityPoints = 33;
}

item_t GoldenShovel::getID(){ return 264;}

WoodenAxe::WoodenAxe():BaseItem()
{
	textureRow = 8;

	plane = 4;
	durabilityPoints = 60;
}

item_t WoodenAxe::getID(){ return 265;}

StoneAxe::StoneAxe():BaseItem()
{
	textureRow = 8;

	plane = 3;
	durabilityPoints = 132;
}

item_t StoneAxe::getID(){ return 266;}

IronAxe::IronAxe():BaseItem()
{
	textureRow = 8;

	plane = 2;
	durabilityPoints = 251;
}

item_t IronAxe::getID(){ return 267;}

DiamondAxe::DiamondAxe():BaseItem()
{
	textureRow = 8;

	plane = 1;
	durabilityPoints = 1562;
}

item_t DiamondAxe::getID(){ return 268;}

GoldenAxe::GoldenAxe():BaseItem()
{
	textureRow = 8;

	plane = 0;
	durabilityPoints = 33;
}

item_t GoldenAxe::getID(){ return 269;}

WoodenHoe::WoodenHoe():BaseItem()
{
	textureRow = 7;

	plane = 4;
	durabilityPoints = 60;
}

item_t WoodenHoe::getID(){ return 270;}

StoneHoe::StoneHoe():BaseItem()
{
	textureRow = 7;

	plane = 3;
	durabilityPoints = 132;
}

item_t StoneHoe::getID(){ return 271;}

IronHoe::IronHoe():BaseItem()
{
	textureRow = 7;

	plane = 2;
	durabilityPoints = 251;
}

item_t IronHoe::getID(){ return 272;}

DiamondHoe::DiamondHoe():BaseItem()
{
	textureRow = 7;

	plane = 1;
	durabilityPoints = 1562;
}

item_t DiamondHoe::getID(){ return 273;}

GoldenHoe::GoldenHoe():BaseItem()
{
	textureRow = 7;

	plane = 0;
	durabilityPoints = 33;
}

item_t GoldenHoe::getID(){ return 274;}

Scissors::Scissors():BaseItem()
{
	textureRow = 10;

	plane = 13;
	durabilityPoints = 239;
}

item_t Scissors::getID(){ return 275;}

Stick::Stick():BaseItem()
{
	textureRow = 12;

	plane = 5;
}

item_t Stick::getID(){ return 276;}

Coal::Coal():BaseItem()
{
	textureRow = 15;

	plane = 7;
}

item_t Coal::getID(){ return 277;}

IronBar::IronBar():BaseItem()
{
	textureRow = 14;

	plane = 7;
}

item_t IronBar::getID(){ return 278;}

DiamondItem::DiamondItem():BaseItem()
{
	textureRow = 12;

	plane = 7;
}

item_t DiamondItem::getID(){ return 279;}

GoldenBar::GoldenBar():BaseItem()
{
	textureRow = 13;

	plane = 7;
}

item_t GoldenBar::getID(){ return 280;}

FireItem::FireItem():BaseItem()
{
	textureRow = 0;

	plane = 0;
}

item_t FireItem::getID(){ return 281;}

LigniteCoal::LigniteCoal():BaseItem()
{
	textureRow = 14;

	plane = 9;
}

item_t LigniteCoal::getID(){ return 282;}

Clay::Clay():BaseItem()
{
	textureRow = 12;

	plane = 9;

	furnItem = 289;
}

item_t Clay::getID(){ return 283;}


Apple::Apple():BaseItem()
{
	textureRow = 15;

	plane = 10;
}

item_t Apple::getID(){ return 284;}


GoldenApple::GoldenApple():BaseItem()
{
	textureRow = 15;

	plane = 11;
}

item_t GoldenApple::getID(){ return 285;}

WheatSeeds::WheatSeeds():BaseItem()
{
	textureRow = 15;

	plane = 9;
}

item_t WheatSeeds::getID(){ return 286;}

Wheat::Wheat():BaseItem()
{
	textureRow = 14;

	plane = 9;
}

item_t Wheat::getID(){ return 287;}


WhiteBread::WhiteBread():BaseItem()
{
	textureRow = 13;

	plane = 9;
}

item_t WhiteBread::getID(){ return 288;}

Brick::Brick():BaseItem()
{
	textureRow = 14;

	plane = 6;
}

item_t Brick::getID(){ return 289;}

Busket::Busket():BaseItem()
{
	textureRow = 11;

	plane = 10;
}

item_t Busket::getID(){ return 290;}

WaterBusket::WaterBusket():BaseItem()
{
	textureRow = 11;

	plane = 11;
}

item_t WaterBusket::getID(){ return 291;}

LavaBusket::LavaBusket():BaseItem()
{
	textureRow = 11;

	plane = 12;
}

item_t LavaBusket::getID(){ return 292;}

CaneItem::CaneItem():BaseItem()
{
	textureRow = 14;

	plane = 11;
}

item_t CaneItem::getID(){ return 293;}

Flower1Item::Flower1Item():BaseItem()
{
	textureRow = 2;

	plane = 0;
}

item_t Flower1Item::getID(){ return 294;}

Flower2Item::Flower2Item():BaseItem()
{
	textureRow = 2;

	plane = 1;
}

item_t Flower2Item::getID(){ return 295;}

OakSaplingItem::OakSaplingItem():BaseItem()
{
	textureRow = 1;

	plane = 2;
}

item_t OakSaplingItem::getID(){ return 296;}

Paper::Paper():BaseItem()
{
	textureRow = 12;

	plane = 10;
}

item_t Paper::getID(){ return 297;}

Book::Book():BaseItem()
{
	textureRow = 12;

	plane = 11;
}

item_t Book::getID(){ return 298;}

SnowBallItem::SnowBallItem():BaseItem()
{
	textureRow = 15;

	plane = 14;
}

item_t SnowBallItem::getID(){ return 299;}

MooshroomItem1::MooshroomItem1():BaseItem()
{
	textureRow = 1;

	plane = 0;
}

item_t MooshroomItem1::getID(){ return 300;}


MooshroomItem2::MooshroomItem2():BaseItem()
{
	textureRow = 1;

	plane = 1;
}

item_t MooshroomItem2::getID(){ return 301;}

Bowl::Bowl():BaseItem()
{
	textureRow = 11;

	plane = 7;
}

item_t Bowl::getID(){ return 302;}

MooshroomBowl::MooshroomBowl():BaseItem()
{
	textureRow = 11;

	plane = 8;
}

item_t MooshroomBowl::getID(){ return 303;}

IronWateringCan::IronWateringCan():BaseItem()
{
	textureRow = 1;

	plane = 3;
}

item_t IronWateringCan::getID(){ return 304;}

DiamondWateringCan::DiamondWateringCan():BaseItem()
{
	textureRow = 1;

	plane = 4;
}

item_t DiamondWateringCan::getID(){ return 305;}

DoorItem::DoorItem():BaseItem()
{
	textureRow = 13;

	plane = 11;
}

item_t DoorItem::getID(){ return 306;}

LadderItem::LadderItem():BaseItem()
{
	textureRow = 2;

	plane = 2;
}

item_t LadderItem::getID(){ return 307;}

TorchItem::TorchItem():BaseItem()
{
	textureRow = 3;

	plane = 0;
}

item_t TorchItem::getID(){ return 308;}

SpruceSaplingItem::SpruceSaplingItem():BaseItem()
{
	textureRow = 0;

	plane = 2;
}

item_t SpruceSaplingItem::getID(){ return 309;}

BirchSaplingItem::BirchSaplingItem():BaseItem()
{
	textureRow = 0;

	plane = 3;
}

item_t BirchSaplingItem::getID(){ return 310;}

MelonItem::MelonItem():BaseItem()
{
	textureRow = 9;

	plane = 13;
}

item_t MelonItem::getID(){ return 311;}

MelonSeeds::MelonSeeds():BaseItem()
{
	textureRow = 12;

	plane = 14;
}

item_t MelonSeeds::getID(){ return 312;}

Sugar::Sugar():BaseItem()
{
	textureRow = 15;

	plane = 13;
}

item_t Sugar::getID(){ return 313;}

CocoaBeans::CocoaBeans():BaseItem()
{
	textureRow = 8;

	plane = 14;
}

item_t CocoaBeans::getID(){ return 314;}

Cookie::Cookie():BaseItem()
{
	textureRow = 10;

	plane = 12;
}

item_t Cookie::getID(){ return 315;}

RawBeef::RawBeef():BaseItem()
{
	textureRow = 9;

	plane = 9;
	furnItem = 317;
}

item_t RawBeef::getID(){ return 316;}

Steak::Steak():BaseItem()
{
	textureRow = 9;

	plane = 10;
}

item_t Steak::getID(){ return 317;}

LapisLazuli::LapisLazuli():BaseItem()
{
	textureRow = 7;

	plane = 14;
}

item_t LapisLazuli::getID(){ return 318;}

MilkBusket::MilkBusket():BaseItem()
{
	textureRow = 11;

	plane = 13;
}

item_t MilkBusket::getID(){ return 319;}

CakeItem::CakeItem():BaseItem()
{
	textureRow = 14;

	plane = 13;
}

item_t CakeItem::getID(){ return 320;}

Bone::Bone():BaseItem()
{
	textureRow = 14;

	plane = 12;
}

item_t Bone::getID(){ return 321;}

BoneMeal::BoneMeal():BaseItem()
{
	textureRow = 4;

	plane = 15;
}

item_t BoneMeal::getID(){ return 322;}

Leather::Leather():BaseItem()
{
	textureRow = 9;

	plane = 7;
}

item_t Leather::getID(){ return 323;}

SampleHelmet::SampleHelmet():BaseItem()
{
	textureRow = 15;

	plane = 15;
}

item_t SampleHelmet::getID(){ return 324;}

SampleChestplate::SampleChestplate():BaseItem()
{
	textureRow = 14;

	plane = 15;
}

item_t SampleChestplate::getID(){ return 325;}

SampleLeggings::SampleLeggings():BaseItem()
{
	textureRow = 13;

	plane = 15;
}

item_t SampleLeggings::getID(){ return 326;}

SampleBoots::SampleBoots():BaseItem()
{
	textureRow = 12;

	plane = 15;
}

item_t SampleBoots::getID(){ return 327;}

LeatherHelmet::LeatherHelmet():BaseItem()
{
	textureRow = 15;

	plane = 0;
	itemType = 'H';
	durabilityPoints = 55;
}

item_t LeatherHelmet::getID(){ return 328;}

LeatherChestplate::LeatherChestplate():BaseItem()
{
	textureRow = 14;

	plane = 0;
	itemType = 'C';
	durabilityPoints = 80;
}

item_t LeatherChestplate::getID(){ return 329;}

LeatherLeggings::LeatherLeggings():BaseItem()
{
	textureRow = 13;

	plane = 0;
	itemType = 'L';
	durabilityPoints = 75;
}

item_t LeatherLeggings::getID(){ return 330;}

LeatherBoots::LeatherBoots():BaseItem()
{
	textureRow = 12;

	plane = 0;
	itemType = 'B';
	durabilityPoints = 65;
}

item_t LeatherBoots::getID(){ return 331;}

ChainmailHelmet::ChainmailHelmet():BaseItem()
{
	textureRow = 15;

	plane = 1;
	itemType = 'H';
	durabilityPoints = 165;
}

item_t ChainmailHelmet::getID(){ return 332;}

ChainmailChestplate::ChainmailChestplate():BaseItem()
{
	textureRow = 14;

	plane = 1;
	itemType = 'C';
	durabilityPoints = 240;
}

item_t ChainmailChestplate::getID(){ return 333;}

ChainmailLeggings::ChainmailLeggings():BaseItem()
{
	textureRow = 13;

	plane = 1;
	itemType = 'L';
	durabilityPoints = 225;
}

item_t ChainmailLeggings::getID(){ return 334;}

ChainmailBoots::ChainmailBoots():BaseItem()
{
	textureRow = 12;

	plane = 1;
	itemType = 'B';
	durabilityPoints = 195;
}

item_t ChainmailBoots::getID(){ return 335;}

IronHelmet::IronHelmet():BaseItem()
{
	textureRow = 15;

	plane = 2;
	itemType = 'H';
	durabilityPoints = 165;
}

item_t IronHelmet::getID(){ return 336;}

IronChestplate::IronChestplate():BaseItem()
{
	textureRow = 14;

	plane = 2;
	itemType = 'C';
	durabilityPoints = 240;
}

item_t IronChestplate::getID(){ return 337;}

IronLeggings::IronLeggings():BaseItem()
{
	textureRow = 13;

	plane = 2;
	itemType = 'L';
	durabilityPoints = 225;
}

item_t IronLeggings::getID(){ return 338;}

IronBoots::IronBoots():BaseItem()
{
	textureRow = 12;

	plane = 2;
	itemType = 'B';
	durabilityPoints = 195;
}

item_t IronBoots::getID(){ return 339;}

DiamondHelmet::DiamondHelmet():BaseItem()
{
	textureRow = 15;

	plane = 3;
	itemType = 'H';
	durabilityPoints = 363;
}

item_t DiamondHelmet::getID(){ return 340;}

DiamondChestplate::DiamondChestplate():BaseItem()
{
	textureRow = 14;

	plane = 3;
	itemType = 'C';
	durabilityPoints = 528;
}

item_t DiamondChestplate::getID(){ return 341;}

DiamondLeggings::DiamondLeggings():BaseItem()
{
	textureRow = 13;

	plane = 3;
	itemType = 'L';
	durabilityPoints = 495;
}

item_t DiamondLeggings::getID(){ return 342;}

DiamondBoots::DiamondBoots():BaseItem()
{
	textureRow = 12;

	plane = 3;
	itemType = 'B';
	durabilityPoints = 429;
}

item_t DiamondBoots::getID(){ return 343;}

GoldenHelmet::GoldenHelmet():BaseItem()
{
	textureRow = 15;

	plane = 4;
	itemType = 'H';
	durabilityPoints = 77;
}

item_t GoldenHelmet::getID(){ return 344;}

GoldenChestplate::GoldenChestplate():BaseItem()
{
	textureRow = 14;

	plane = 4;
	itemType = 'C';
	durabilityPoints = 112;
}

item_t GoldenChestplate::getID(){ return 345;}

GoldenLeggings::GoldenLeggings():BaseItem()
{
	textureRow = 13;

	plane = 4;
	itemType = 'L';
	durabilityPoints = 105;
}

item_t GoldenLeggings::getID(){ return 346;}

GoldenBoots::GoldenBoots():BaseItem()
{
	textureRow = 12;

	plane = 4;
	itemType = 'B';
	durabilityPoints = 91;
}

item_t GoldenBoots::getID(){ return 347;}

RottenFlesh::RottenFlesh():BaseItem()
{
	textureRow = 10;

	plane = 11;
}

item_t RottenFlesh::getID(){ return 348;}

















