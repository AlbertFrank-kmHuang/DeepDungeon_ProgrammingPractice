#include "enemy_config.h"
#include "character_config.h"
#include <random>

// 构造函数
Enemy::Enemy(const std::string& name,int level,CharacterClass job,EnemyType entype)
    : Character(name, job, level, 0.2f, 1.0f, 0, 0,true, false),
    entype(entype){}

//敌方剑士
Warrior_enemy::Warrior_enemy(const std::string& name, EnemyType entype,int level):
    Enemy::Enemy(name,level,CharacterClass::Warrior,entype){
    if(entype==EnemyType::Normal){
        if(level==1){
            maxHealth=130;
            maxmana=50;
            attack=10;
            defense=10;
            critrate=0.2;
            critdamage=1.0;
            missrate=0;
        }
        else if(level==2){
            maxHealth=140;
            maxmana=70;
            attack=15;
            defense=15;
            critrate=0.3;
            critdamage=1.2;
            missrate=0;
        }
        else if(level==3){
            maxHealth=180;
            maxmana=100;
            attack=25;
            defense=25;
            critrate=0.5;
            critdamage=1.5;
            missrate=0.1;
        }
    }
    else if(entype==EnemyType::Elite){
        if(level==1){
            maxHealth=150;
            maxmana=50;
            attack=20;
            defense=20;
            critrate=0.2;
            critdamage=1.0;
            missrate=0;
        }
        else if(level==2){
            maxHealth=180;
            maxmana=70;
            attack=30;
            defense=30;
            critrate=0.3;
            critdamage=1.2;
            missrate=0;
        }
        else if(level==3){
            maxHealth=240;
            maxmana=100;
            attack=50;
            defense=50;
            critrate=0.5;
            critdamage=1.5;
            missrate=0.1;
        }
    }
    else if(entype==EnemyType::Boss){
        if(level==1){
            maxHealth=200;
            maxmana=70;
            attack=20;
            defense=20;
            critrate=0.2;
            critdamage=1.0;
            missrate=0;
        }
        else if(level==2){
            maxHealth=250;
            maxmana=100;
            attack=30;
            defense=30;
            critrate=0.3;
            critdamage=1.2;
            missrate=0;
        }
        else if(level==3){
            maxHealth=400;
            maxmana=150;
            attack=50;
            defense=50;
            critrate=0.5;
            critdamage=1.5;
            missrate=0.1;
        }
    }
    mana=maxmana;
    health=maxHealth;
}

Mage_enemy::Mage_enemy(const std::string& name, EnemyType entype,int level):
    Enemy::Enemy(name,level,CharacterClass::Mage,entype){
    if(entype==EnemyType::Normal){
        if(level==1){
            maxHealth=80;
            maxmana=100;
            attack=10;
            defense=0;
            critrate=0.2;
            critdamage=1.0;
            missrate=0;
        }
        else if(level==2){
            maxHealth=90;
            maxmana=120;
            attack=20;
            defense=10;
            critrate=0.3;
            critdamage=1.2;
            missrate=0;
        }
        else if(level==3){
            maxHealth=110;
            maxmana=150;
            attack=40;
            defense=25;
            critrate=0.5;
            critdamage=1.5;
            missrate=0.1;
        }
    }
    else if(entype==EnemyType::Elite){
        if(level==1){
            maxHealth=100;
            maxmana=100;
            attack=10;
            defense=10;
            critrate=0.2;
            critdamage=1.0;
            missrate=0;
        }
        else if(level==2){
            maxHealth=120;
            maxmana=120;
            attack=20;
            defense=20;
            critrate=0.3;
            critdamage=1.2;
            missrate=0;
        }
        else if(level==3){
            maxHealth=150;
            maxmana=150;
            attack=40;
            defense=40;
            critrate=0.5;
            critdamage=1.5;
            missrate=0.1;
        }
    }
    else if(entype==EnemyType::Boss){
        if(level==1){
            maxHealth=200;
            maxmana=120;
            attack=15;
            defense=5;
            critrate=0.2;
            critdamage=1.0;
            missrate=0;
        }
        else if(level==2){
            maxHealth=250;
            maxmana=150;
            attack=25;
            defense=15;
            critrate=0.3;
            critdamage=1.2;
            missrate=0;
        }
        else if(level==3){
            maxHealth=400;
            maxmana=200;
            attack=45;
            defense=35;
            critrate=0.5;
            critdamage=1.5;
            missrate=0.1;
        }
    }
    health=maxHealth;
    mana=maxmana;
}

Archer_enemy::Archer_enemy(const std::string& name, EnemyType entype,int level):
    Enemy::Enemy(name,level,CharacterClass::Archer,entype){
    if(entype==EnemyType::Normal){
        if(level==1){
            maxHealth=80;
            maxmana=50;
            attack=10;
            defense=0;
            critrate=0.2;
            critdamage=1.0;
            missrate=0;
        }
        else if(level==2){
            maxHealth=90;
            maxmana=70;
            attack=20;
            defense=10;
            critrate=0.3;
            critdamage=1.2;
            missrate=0;
        }
        else if(level==3){
            maxHealth=110;
            maxmana=100;
            attack=40;
            defense=25;
            critrate=0.5;
            critdamage=1.5;
            missrate=0.1;
        }
    }
    else if(entype==EnemyType::Elite){
        if(level==1){
            maxHealth=90;
            maxmana=50;
            attack=15;
            defense=5;
            critrate=0.2;
            critdamage=1.0;
            missrate=0;
        }
        else if(level==2){
            maxHealth=110;
            maxmana=70;
            attack=25;
            defense=15;
            critrate=0.3;
            critdamage=1.2;
            missrate=0;
        }
        else if(level==3){
            maxHealth=140;
            maxmana=100;
            attack=45;
            defense=35;
            critrate=0.5;
            critdamage=1.5;
            missrate=0.1;
        }
    }
    else if(entype==EnemyType::Boss){
        if(level==1){
            maxHealth=200;
            maxmana=70;
            attack=15;
            defense=5;
            critrate=0.2;
            critdamage=1.0;
            missrate=0;
        }
        else if(level==2){
            maxHealth=250;
            maxmana=100;
            attack=25;
            defense=15;
            critrate=0.3;
            critdamage=1.2;
            missrate=0;
        }
        else if(level==3){
            maxHealth=400;
            mana=150;
            attack=45;
            defense=35;
            critrate=0.5;
            critdamage=1.5;
            missrate=0.1;
        }
    }
    health=maxHealth;
}

Nonamer_enemy::Nonamer_enemy(const std::string& name, EnemyType entype,int level):
    Enemy::Enemy(name,level,CharacterClass::Nonamer,entype){
    if(entype==EnemyType::Normal){
        if(level==1){
            maxHealth=90;
            maxmana=100;
            attack=5;
            defense=10;
            critrate=0.2;
            critdamage=1.0;
            missrate=0;
        }
        else if(level==2){
            maxHealth=100;
            maxmana=120;
            attack=15;
            defense=20;
            critrate=0.3;
            critdamage=1.2;
            missrate=0;
        }
        else if(level==3){
            maxHealth=120;
            maxmana=150;
            attack=35;
            defense=40;
            critrate=0.5;
            critdamage=1.5;
            missrate=0.1;
        }
    }
    else if(entype==EnemyType::Elite){
        if(level==1){
            maxHealth=100;
            maxmana=100;
            attack=10;
            defense=10;
            critrate=0.2;
            critdamage=1.0;
            missrate=0;
        }
        else if(level==2){
            maxHealth=120;
            maxmana=120;
            attack=20;
            defense=20;
            critrate=0.3;
            critdamage=1.2;
            missrate=0;
        }
        else if(level==3){
            maxHealth=150;
            maxmana=150;
            attack=40;
            defense=40;
            critrate=0.5;
            critdamage=1.5;
            missrate=0.1;
        }
    }
    else if(entype==EnemyType::Boss){
        if(level==1){
            maxHealth=200;
            maxmana=120;
            attack=10;
            defense=10;
            critrate=0.2;
            critdamage=1.0;
            missrate=0;
        }
        else if(level==2){
            maxHealth=250;
            maxmana=150;
            attack=20;
            defense=20;
            critrate=0.3;
            critdamage=1.2;
            missrate=0;
        }
        else if(level==3){
            maxHealth=400;
            maxmana=200;
            attack=40;
            defense=40;
            critrate=0.5;
            critdamage=1.5;
            missrate=0.1;
        }
    }
    mana=maxmana;
    health=maxHealth;
}

// AI策略
Skill* Enemy::AIStrategy() {
    // 血量低于50%,50%概率治疗
    if (getHealth() < getMaxHealth() * 0.5f) {
        static std::random_device rd;
        static std::mt19937 gen(rd());
        std::uniform_real_distribution<> dis(0.0, 1.0);
        float randomValue = dis(gen);
        if(randomValue<=0.5){
            for (int i = 0; i < skills.size(); ++i) {
                if (skills[i]->getname() == "治疗"&&skills[i]->getmanacost()<mana+manaadd) {
                    return skills[i];
                }
            }
        }
    }

    // 如果血量低于50%,50%概率防御
    if (getHealth() < getMaxHealth() * 0.5f) {
        static std::random_device rd;
        static std::mt19937 gen(rd());
        std::uniform_real_distribution<> dis(0.0, 1.0);
        float randomValue = dis(gen);
        if(randomValue<=0.5){
            for (int i = 0; i < skills.size(); ++i) {
                if (skills[i]->getname() == "防御反击"&&skills[i]->getmanacost()<mana+manaadd) {
                    return skills[i];
                }
            }
        }
    }

    //50%概率上buff
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0.0, 1.0);
    float randomValue = dis(gen);
    if(randomValue<=0.5){
        for (int i = 0; i < skills.size(); ++i) {
            if (skills[i]->getname() == "buff"&&skills[i]->getmanacost()<mana+manaadd) {
                return skills[i];
            }
        }
    }

    //都不行则普通攻击
    return skills[0];
}

// 剑士类敌人实现
BerserkerWarrior::BerserkerWarrior(const std::string& name, EnemyType entype, int level)
    : Warrior_enemy(name, entype, level) {

    // 治疗技能：狂怒治疗
    healSkill* heal = new healSkill(1, "治疗", 20, 0.2f, "消耗20点法力，恢复自身20%生命值");
    skills.push_back(heal);

    // 防御反击技能：狂战士之怒
    buffSkill* defense = new buffSkill(2, "防御反击", Status::Defend, 1, 0.5f,
                                       "消耗20点法力，进入防御状态，减伤50%并反击", 20);
    skills.push_back(defense);

    // buff技能：狂暴之力
    buffSkill* buff = new buffSkill(3, "buff", Status::attackAdd, 3, 0.3f,
                                    "消耗20点法力，提升30%攻击力，持续3回合", 20);
    skills.push_back(buff);
}

IronGuard::IronGuard(const std::string& name, EnemyType entype, int level)
    : Warrior_enemy(name, entype, level) {

    // 治疗技能：钢铁意志
    healSkill* heal = new healSkill(1, "治疗", 30, 0.3f, "消耗30点法力，恢复自身30%生命值");
    skills.push_back(heal);

    // 防御反击技能：钢铁壁垒
    buffSkill* defense = new buffSkill(2, "防御反击", Status::Defend, 1, 0.5f,
                                       "消耗20点法力，进入防御状态2回合，减伤50%并反击", 20);
    skills.push_back(defense);

    // buff技能：钢铁守护
    buffSkill* buff = new buffSkill(3, "buff", Status::defenseAdd, 3, 0.3f,
                                    "消耗20点法力，提升30%防御力，持续3回合", 20);
    skills.push_back(buff);
}

BloodBlade::BloodBlade(const std::string& name, EnemyType entype, int level)
    : Warrior_enemy(name, entype, level) {

    // 治疗技能：嗜血恢复
    healSkill* heal = new healSkill(1, "治疗", 30, 0.2f, "消耗30点法力，恢复自身20%生命值");
    skills.push_back(heal);

    // 防御反击技能：鲜血壁垒
    buffSkill* defense = new buffSkill(2, "防御反击", Status::Defend, 1, 0.5f,
                                       "消耗20点法力，进入防御状态，减伤50%并反击", 20);
    skills.push_back(defense);

    // buff技能：嗜血狂怒
    buffSkill* buff = new buffSkill(3, "buff", Status::LifeSteal, 2, 0.3f,
                                    "消耗30点法力，获得2回合30%吸血效果", 30);
    skills.push_back(buff);
}

Breaker::Breaker(const std::string& name, EnemyType entype, int level)
    : Warrior_enemy(name, entype, level) {

    // 治疗技能：坚韧恢复
    healSkill* heal = new healSkill(1, "治疗", 20, 0.2f, "消耗20点法力，恢复自身20%生命值");
    skills.push_back(heal);

    // 防御反击技能：不动如山
    buffSkill* defense = new buffSkill(2, "防御反击", Status::Defend, 1, 0.5f,
                                       "消耗20点法力，进入防御状态，减伤50%并反击", 20);
    skills.push_back(defense);

    // buff技能：破甲之势
    buffSkill* buff = new buffSkill(3, "buff", Status::Penetration, 2, 0,
                                    "消耗30点法力，获得2回合穿透效果", 30);
    skills.push_back(buff);
}

SwordMaster::SwordMaster(const std::string& name, EnemyType entype, int level)
    : Warrior_enemy(name, entype, level) {

    // 治疗技能：宗师冥想
    healSkill* heal = new healSkill(1, "治疗", 30, 0.3f, "消耗30点法力，恢复自身30%生命值");
    skills.push_back(heal);

    // 防御反击技能：剑心通明
    buffSkill* defense = new buffSkill(2, "防御反击", Status::Defend, 1, 0.5f,
                                       "消耗20点法力，进入防御状态，减伤50%并反击", 20);
    skills.push_back(defense);

    // buff技能：剑意爆发
    buffSkill* buff = new buffSkill(3, "buff", Status::critdamageAdd, 3, 0.3f,
                                    "消耗20点法力，提升30%暴击伤害，持续3回合", 20);
    skills.push_back(buff);
}

// 法师类敌人实现
FireMage::FireMage(const std::string& name, EnemyType entype, int level)
    : Mage_enemy(name, entype, level) {

    // 治疗技能：火焰治疗
    healSkill* heal = new healSkill(1, "治疗", 30, 0.2f, "消耗30点法力，恢复自身20%生命值");
    skills.push_back(heal);

    // 防御反击技能：火焰护盾
    buffSkill* defense = new buffSkill(2, "防御反击", Status::Defend, 1, 0.5f,
                                       "消耗30点法力，进入防御状态，减伤50%并反击", 30);
    skills.push_back(defense);

    // buff技能：火焰强化
    buffSkill* buff = new buffSkill(3, "buff", Status::manaAdd, 2, 0.3f,
                                    "回复30%法力，持续2回合", 0);
    skills.push_back(buff);
}

FrostMage::FrostMage(const std::string& name, EnemyType entype, int level)
    : Mage_enemy(name, entype, level) {

    // 治疗技能：冰霜治疗
    healSkill* heal = new healSkill(1, "治疗", 20, 0.2f, "消耗20点法力，恢复自身30%生命值");
    skills.push_back(heal);

    // 防御反击技能：冰霜屏障
    buffSkill* defense = new buffSkill(2, "防御反击", Status::Defend, 1, 0.5f,
                                       "消耗30点法力，进入防御状态，减伤50%并反击", 30);
    skills.push_back(defense);

    // buff技能：冰霜减速
    buffSkill* buff = new buffSkill(3, "buff", Status::Paralyzed, 2, 0,
                                    "消耗30点法力，使目标麻痹2回合", 30);
    skills.push_back(buff);
}

ShadowMage::ShadowMage(const std::string& name, EnemyType entype, int level)
    : Mage_enemy(name, entype, level) {

    // 治疗技能：暗影汲取
    healSkill* heal = new healSkill(1, "治疗", 20, 0.3f, "消耗20点法力，恢复自身30%生命值");
    skills.push_back(heal);

    // 防御反击技能：暗影护盾
    buffSkill* defense = new buffSkill(2, "防御反击", Status::Defend, 1, 0.5f,
                                       "消耗30点法力，进入防御状态，减伤50%并反击", 30);
    skills.push_back(defense);

    // buff技能：暗影诅咒
    buffSkill* buff = new buffSkill(3, "buff", Status::attackDec, 2, -0.3f,
                                    "消耗20点法力，降低目标30%攻击力，持续2回合", 20);
    skills.push_back(buff);
}

ElementalMage::ElementalMage(const std::string& name, EnemyType entype, int level)
    : Mage_enemy(name, entype, level) {

    // 治疗技能：元素治疗
    healSkill* heal = new healSkill(1, "治疗", 20, 0.3f, "消耗20点法力，恢复自身30%生命值");
    skills.push_back(heal);

    // 防御反击技能：元素护盾
    buffSkill* defense = new buffSkill(2, "防御反击", Status::Defend, 1, 0.5f,
                                       "消耗30点法力，进入防御状态，减伤50%并反击", 30);
    skills.push_back(defense);

    // buff技能：元素共鸣
    buffSkill* buff = new buffSkill(3, "buff", Status::healthAdd, 2, 0.3f,
                                    "消耗30点法力，提升30%生命上限，持续2回合", 30);
    skills.push_back(buff);
}

Archmage::Archmage(const std::string& name, EnemyType entype, int level)
    : Mage_enemy(name, entype, level) {

    // 治疗技能：奥术治疗
    healSkill* heal = new healSkill(1, "治疗", 50, 0.5f, "消耗50点法力，恢复自身50%生命值");
    skills.push_back(heal);

    // 防御反击技能：奥术屏障
    buffSkill* defense = new buffSkill(2, "防御反击", Status::Defend, 1, 0.5f,
                                       "消耗50点法力，进入防御状态，减伤50%并反击", 50);
    skills.push_back(defense);

    // buff技能：奥术智慧
    buffSkill* buff = new buffSkill(3, "buff", Status::manaAdd, 2, 0.4f,
                                    "提升40%法力上限，持续2回合", 0);
    skills.push_back(buff);
}

// 弓箭手类敌人实现
Sharpshooter::Sharpshooter(const std::string& name, EnemyType entype, int level)
    : Archer_enemy(name, entype, level) {

    // 治疗技能：精准治疗
    healSkill* heal = new healSkill(1, "治疗", 20, 0.2f, "消耗20点法力，恢复自身20%生命值");
    skills.push_back(heal);

    // 防御反击技能：灵活闪避
    buffSkill* defense = new buffSkill(2, "防御反击", Status::Defend, 1, 0.5f,
                                       "消耗20点法力，进入防御状态，减伤50%并反击", 20);
    skills.push_back(defense);

    // buff技能：精准瞄准
    buffSkill* buff = new buffSkill(3, "buff", Status::critrateAdd, 2, 0.3f,
                                    "消耗20点法力，提升30%暴击率，持续2回合", 20);
    skills.push_back(buff);
}

Ranger::Ranger(const std::string& name, EnemyType entype, int level)
    : Archer_enemy(name, entype, level) {

    // 治疗技能：自然治疗
    healSkill* heal = new healSkill(1, "治疗", 20, 0.2f, "消耗20点法力，恢复自身20%生命值");
    skills.push_back(heal);

    // 防御反击技能：游侠防御
    buffSkill* defense = new buffSkill(2, "防御反击", Status::Defend, 1, 0.5f,
                                       "消耗20点法力，进入防御状态，减伤50%并反击", 20);
    skills.push_back(defense);

    // buff技能：猎人印记
    buffSkill* buff = new buffSkill(3, "buff", Status::missrateAdd, 2, 0.2f,
                                    "消耗20点法力，提升20%闪避率，持续2回合", 20);
    skills.push_back(buff);
}

Sniper::Sniper(const std::string& name, EnemyType entype, int level)
    : Archer_enemy(name, entype, level) {

    // 治疗技能：快速包扎
    healSkill* heal = new healSkill(1, "治疗", 30, 0.3f, "消耗30点法力，恢复自身30%生命值");
    skills.push_back(heal);

    // 防御反击技能：狙击姿态
    buffSkill* defense = new buffSkill(2, "防御反击", Status::Defend, 1, 0.5f,
                                       "消耗20点法力，进入防御状态，减伤50%并反击", 20);
    skills.push_back(defense);

    // buff技能：狙击专注
    buffSkill* buff = new buffSkill(3, "buff", Status::critdamageAdd, 2, 0.4f,
                                    "消耗30点法力，提升40%暴击伤害，持续2回合", 30);
    skills.push_back(buff);
}

Hunter::Hunter(const std::string& name, EnemyType entype, int level)
    : Archer_enemy(name, entype, level) {

    // 治疗技能：猎手治疗
    healSkill* heal = new healSkill(1, "治疗", 20, 0.2f, "消耗20点法力，恢复自身15%生命值");
    skills.push_back(heal);

    // 防御反击技能：猎人防御
    buffSkill* defense = new buffSkill(2, "防御反击", Status::Defend, 1, 0.5f,
                                       "消耗20点法力，进入防御状态，减伤50%并反击", 20);
    skills.push_back(defense);

    // buff技能：追踪标记
    buffSkill* buff = new buffSkill(3, "buff", Status::defenseDec, 2, -0.3f,
                                    "消耗30点法力，降低目标30%防御力，持续2回合", 30);
    skills.push_back(buff);
}

ArrowGod::ArrowGod(const std::string& name, EnemyType entype, int level)
    : Archer_enemy(name, entype, level) {

    // 治疗技能：神佑治疗
    healSkill* heal = new healSkill(1, "治疗", 20, 0.2f, "消耗20点法力，恢复自身20%生命值");
    skills.push_back(heal);

    // 防御反击技能：神之庇护
    buffSkill* defense = new buffSkill(2, "防御反击", Status::Defend, 1, 0.5f,
                                       "消耗20点法力，进入防御状态，减伤50%并反击", 20);
    skills.push_back(defense);

    // buff技能：箭神祝福
    buffSkill* buff = new buffSkill(3, "buff", Status::attackAdd, 3, 0.4f,
                                    "消耗40点法力，提升40%攻击力，持续3回合", 40);
    skills.push_back(buff);
}

// 无名之人类敌人实现
ShadowWalker::ShadowWalker(const std::string& name, EnemyType entype, int level)
    : Nonamer_enemy(name, entype, level) {

    // 治疗技能：暗影恢复
    healSkill* heal = new healSkill(1, "治疗", 20, 0.3f, "消耗25点法力，恢复自身30%生命值");
    skills.push_back(heal);

    // 防御反击技能：暗影闪避
    buffSkill* defense = new buffSkill(2, "防御反击", Status::Defend, 1, 0.5f,
                                       "消耗30点法力，进入防御状态，减伤50%并反击", 30);
    skills.push_back(defense);

    // buff技能：暗影强化
    buffSkill* buff = new buffSkill(3, "buff", Status::missrateAdd, 2, 0.3f,
                                    "消耗20点法力，提升30%闪避率，持续2回合", 20);
    skills.push_back(buff);
}

ChaosApostle::ChaosApostle(const std::string& name, EnemyType entype, int level)
    : Nonamer_enemy(name, entype, level) {

    // 治疗技能：混沌治疗
    healSkill* heal = new healSkill(1, "治疗", 20, 0.3f, "消耗20点法力，恢复自身30%生命值");
    skills.push_back(heal);

    // 防御反击技能：混沌护盾
    buffSkill* defense = new buffSkill(2, "防御反击", Status::Defend, 1, 0.5f,
                                       "消耗30点法力，进入防御状态，减伤50%并反击", 30);
    skills.push_back(defense);

    // buff技能：混沌加持
    buffSkill* buff = new buffSkill(3, "buff", Status::manaDec, 2, 0.3f,
                                    "消耗20点法力，减少目标30%法力值，持续2回合", 20);
    skills.push_back(buff);
}

VoidWalker::VoidWalker(const std::string& name, EnemyType entype, int level)
    : Nonamer_enemy(name, entype, level) {

    // 治疗技能：虚空汲取
    healSkill* heal = new healSkill(1, "治疗", 20, 0.3f, "消耗20点法力，恢复自身30%生命值");
    skills.push_back(heal);

    // 防御反击技能：虚空屏障
    buffSkill* defense = new buffSkill(2, "防御反击", Status::Defend, 1, 0.5f,
                                       "消耗30点法力，进入防御状态，减伤50%并反击", 30);
    skills.push_back(defense);

    // buff技能：虚空之力
    buffSkill* buff = new buffSkill(3, "buff", Status::shieldAdd, 2, 0.3f,
                                    "消耗30点法力，获得30%生命值的护盾，持续2回合", 30);
    skills.push_back(buff);
}

Elementalist::Elementalist(const std::string& name, EnemyType entype, int level)
    : Nonamer_enemy(name, entype, level) {

    // 治疗技能：元素恢复
    healSkill* heal = new healSkill(1, "治疗", 20, 0.3f, "消耗20点法力，恢复自身30%生命值");
    skills.push_back(heal);

    // 防御反击技能：元素守护
    buffSkill* defense = new buffSkill(2, "防御反击", Status::Defend, 1, 0.5f,
                                       "消耗30点法力，进入防御状态，减伤50%并反击", 30);
    skills.push_back(defense);

    // buff技能：元素平衡
    buffSkill* buff = new buffSkill(3, "buff", Status::healthAdd, 2, 0.2f,
                                    "消耗20点法力，提升20%生命上限，持续2回合", 20);
    skills.push_back(buff);
}

VoidKing::VoidKing(const std::string& name, EnemyType entype, int level)
    : Nonamer_enemy(name, entype, level) {

    // 治疗技能：虚无恢复
    healSkill* heal = new healSkill(1, "治疗", 20, 0.3f, "消耗20点法力，恢复自身30%生命值");
    skills.push_back(heal);

    // 防御反击技能：虚无壁垒
    buffSkill* defense = new buffSkill(2, "防御反击", Status::Defend, 1, 0.5f,
                                       "消耗30点法力，进入防御状态，减伤50%并反击", 30);
    skills.push_back(defense);

    // buff技能：虚无之力
    buffSkill* buff = new buffSkill(3, "buff", Status::Penetration, 2, 0,
                                    "消耗40点法力，获得2回合穿透效果", 40);
    skills.push_back(buff);
}