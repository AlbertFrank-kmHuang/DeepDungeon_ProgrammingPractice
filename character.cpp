#include "character_config.h"
#include <algorithm>
#include <random>
#include <vector>
#include <sstream>

Character::Character(const std::string& name, CharacterClass job, int level,
                     float critrate, float critdamage, float missrate,
                     int shield, bool isalive, bool isFrontline)
    : name(name), job(job), level(level),
    critrate(critrate), critdamage(critdamage), missrate(missrate),
    shield(shield), isalive(isalive), isFrontline(isFrontline),
    turnCount(0),currentSkillIndex(0),equippedWeapon(nullptr),attackadd(0),
    defenseadd(0),critrateadd(0),critdamageadd(0),missrateadd(0),healthadd(0),manaadd(0){
    skills.push_back(new Skill(0,"普通攻击",0,"进行一次普通攻击"));
}

void Character::takeDamage(int damage) {
    health-=damage;
    if(health<=0){
        health=0;
        isalive=false;
    }
}

void Character::heal(int amount) {
    health = std::min(maxHealth, health + amount);
}

void Character::levelUp() {
    if(level<3){
        level++;
    }
    isalive=true;
    return;
}

std::string Character::getInfo() const {
    std::stringstream ss;
    ss << getJobName() << " " << name << " (等级:" << level << "星)";
    ss << "\n生命: " << health << "/" << maxHealth;
    ss << "  攻击: " << attack << "  防御: " << defense;
    ss << "  法力: " << mana   << "/" << maxmana;
    ss << "  暴击率: " << critrate * 100 << "%";
    ss << "  暴击伤害: " << critdamage * 100 << "%";
    ss << "\n闪避率: " << missrate * 100 << "%";
    ss << "  护盾: " << shield;

    if (!buffs.empty()) {
        ss << "\n状态: ";
        for (const auto& bf : buffs) {
            switch(bf.buff_has) {
            case Status::attackAdd: ss << "攻击↑" << bf.bufftime << " "; break;
            case Status::defenseAdd: ss << "防御↑" << bf.bufftime << " "; break;
            case Status::healthAdd: ss << "生命↑" << bf.bufftime << " "; break;
            case Status::critrateAdd: ss << "暴率↑" << bf.bufftime << " "; break;
            case Status::critdamageAdd: ss << "暴伤↑" << bf.bufftime << " "; break;
            case Status::missrateAdd: ss << "闪避↑" << bf.bufftime << " "; break;
            case Status::shieldAdd: ss << "护盾" << bf.bufftime << " "; break;
            case Status::Poisoned: ss << "中毒" << bf.bufftime << " "; break;
            case Status::Paralyzed: ss << "麻痹" << bf.bufftime << " "; break;
            case Status::Asleep: ss << "睡眠" << bf.bufftime << " "; break;
            case Status::LifeSteal: ss << "吸血" << bf.bufftime << " "; break;
            case Status::Penetration: ss << "穿透" << bf.bufftime << " "; break;
            default: ss << "状态" << bf.bufftime << " ";
            }
        }
    }

    ss << "\n\n技能:";
    for (size_t i = 0; i < skills.size(); i++) {
        ss << "\n" << (i+1) << ". " << skills[i]->getname();
        ss << " [ " << skills[i]->getdescription()<<" ] ";
    }

    if (equippedWeapon) {
        ss << "\n\n装备: " << equippedWeapon->getName();
        ss<< " [ "<<equippedWeapon->getdescription()<<" ] ";
    }

    return ss.str();
}

// 开始回合
bool Character::startTurn() {
    turnCount++;
    for(int i=0;i<buffs.size();i++){
        if(buffs[i].buff_has==Status::Asleep){
            return false;
        }
        else if(buffs[i].buff_has==Status::Charge){
            return false;
        }
        else if(buffs[i].buff_has==Status::Paralyzed){
            //麻痹50%概率无法行动
            static std::random_device rd;
            static std::mt19937 gen(rd());
            std::uniform_real_distribution<> dis(0.0, 1.0);
            float randomValue = dis(gen);
            if(randomValue<=0.5){
                return false;
            }
        }
        else if(buffs[i].buff_has==Status::Poisoned){
            //中毒固定扣除10滴血，无视防御和其他状态
            health-=10;
        }
    }
    return true;
}

// 结束回合
void Character::endTurn() {
    std::vector<buff> rest;
    for(int i=0;i<buffs.size();i++){
        buffs[i].bufftime--;
        if(buffs[i].bufftime>0){
            rest.push_back(buffs[i]);
        }
    }
    buffs=std::move(rest);
}

//添加武器
void Character::setWeapon(Weapon* weapon){
    equippedWeapon=weapon;
    if(equippedWeapon!=nullptr){
        attackadd=int(equippedWeapon->getAttackBonus()*attack);
        defenseadd=int(equippedWeapon->getDefenseBonus()*defense);
        critrateadd=equippedWeapon->getCritrateBonus();
        critdamageadd=equippedWeapon->getCritdamageBonus();
        missrateadd=equippedWeapon->getMissrateBonus();
        healthadd=int(equippedWeapon->getHealthBonus()*maxHealth);
        manaadd=int(equippedWeapon->getManaBonus()*maxmana);
    }
    else{
        attackadd=0;
        defenseadd=0;
        critrateadd=0;
        critdamageadd=0;
        missrateadd=0;
        manaadd=0;
    }
}

//移除武器
void Character::removeWeapon(){
    equippedWeapon=nullptr;
    attackadd=0;
    defenseadd=0;
    critrateadd=0;
    critdamageadd=0;
    missrateadd=0;
    manaadd=0;
}

// 添加技能
void Character::addSkill(Skill* skill) {
    skills.push_back(skill);
}

bool Skill::execute(Character* caster, Character* target){
    //需要补全！这是个普通伤害的技能。
    return true;
}

bool healSkill::execute(Character* caster, Character* target) {
    if (!target || !target->alive()||!caster||!caster->alive()) return false;
    if(target->getmana()+target->getmanaadd()<manacost) return false;

    target->heal(int(healmount*target->getMaxHealth()));

    // 消耗法力
    if(caster->getmana()<manacost){
        caster->setmanaadd(manacost-caster->getmana());
        caster->setmana(0);
    }
    else{
        caster->setmana(caster->getmana()-manacost);
    }
    return true;
}

bool buffSkill::execute(Character* caster, Character* target) {
    if (!target || !target->alive()||!caster||!caster->alive()) return false;
    int buffmount=0;

    // 如果是护盾，计算护盾值
    if (buff_add == Status::shieldAdd) {
        buffmount=int(target->getMaxHealth() * add);
        target->setShield(buffmount);
    }
    else if (buff_add==Status::healthAdd){
        buffmount=int(target->getMaxHealth()*add);
        target->sethealthadd(buffmount);
    }
    else if(buff_add==Status::defenseAdd){
        buffmount=int(target->getDefense()*add);
        target->setdefenseadd(buffmount);
    }
    else if(buff_add==Status::attackAdd){
        buffmount=int(target->getAttack()*add);
        target->setattackadd(buffmount);
    }
    else if(buff_add==Status::critrateAdd){
        buffmount=add;
        target->setcritrateadd(buffmount);
    }
    else if(buff_add==Status::critdamageAdd){
        buffmount=add;
        target->setcritdamageadd(buffmount);
    }
    else if(buff_add==Status::missrateAdd){
        buffmount=add;
        target->setmissrateadd(buffmount);
    }
    else if(buff_add==Status::manaAdd){
        buffmount=int(target->getmaxmana()*add);
        target->setmanaadd(buffmount);
    }
    else if(buff_add==Status::defenseDec){
        buffmount=int(target->getDefense()*add);
        target->setdefenseadd(buffmount);
    }
    else if(buff_add==Status::attackDec){
        buffmount=int(target->getAttack()*add);
        target->setattackadd(buffmount);
    }
    else if(buff_add==Status::manaDec){
        buffmount=int(target->getmaxmana()*add);
        target->setattackadd(buffmount);
    }
    target->addbuff(buff(buff_add,duringtime,buffmount));
    // 消耗法力
    if(caster->getmana()<manacost){
        caster->setmanaadd(manacost-caster->getmana());
        caster->setmana(0);
    }
    else{
        caster->setmana(caster->getmana()-manacost);
    }
    return true;
}

bool Character::useSkill(int skillIndex, Character* target) {
    if (skillIndex < 0 || skillIndex >= skills.size()) {
        return false;
    }
    Skill* skill = skills[skillIndex];
    bool result=skill->execute(this,target);
    return result;
}

// Warrior 类实现
Warrior::Warrior(const std::string& name, int level)
    : Character(name, CharacterClass::Warrior, level){
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
    health = maxHealth;
    mana=maxmana;
}

void Warrior::levelUp(){
    Character::levelUp();
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
    health = maxHealth;
    mana=maxmana;
    return;
}

// Mage 类实现
Mage::Mage(const std::string& name, int level)
    : Character(name, CharacterClass::Mage, level){
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
    health = maxHealth;
    mana=maxmana;
}

void Mage::levelUp() {
    Character::levelUp();
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
    health = maxHealth;
    mana=maxmana;
    manaadd=int(equippedWeapon->getManaBonus()*mana);
}

//Archer类实现
Archer::Archer(const std::string& name, int level)
    : Character(name, CharacterClass::Warrior, level){
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
    health = maxHealth;
    mana=maxmana;
}

void Archer::levelUp(){
    Character::levelUp();
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
    health = maxHealth;
    mana=maxmana;
    return;
}

//Nonamer类实现
Nonamer::Nonamer(const std::string& name, int level)
    : Character(name, CharacterClass::Warrior, level){
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
    health = maxHealth;
    mana=maxmana;
}

void Nonamer::levelUp(){
    Character::levelUp();
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
    health = maxHealth;
    return;
}

// CharacterManager 类实现
void CharacterManager::addCharacter(Character* character) {
    characters.push_back(character);
}

Character* CharacterManager::findCharacter(const std::string& name) const {
    auto it = std::find_if(characters.begin(), characters.end(),
                           [&name](const Character* & ch) {
                               return ch->getName() == name;
                           });

    return (it != characters.end()) ? *it : nullptr;
}

bool CharacterManager::removeCharacter(const std::string& name) {
    auto it = std::remove_if(characters.begin(), characters.end(),
                             [&name](const Character* & ch) {
                                 return ch->getName() == name;
                             });

    if (it != characters.end()) {
        characters.erase(it, characters.end());
        return true;
    }
    return false;
}

//具体角色的实现
// 1. 剑士 - 莱昂（输出型剑士）
Leon::Leon(const std::string& name, int level)
    : Warrior(name, level) {

    // 技能1：重击
    Skill* heavyStrike = new buffSkill(1,"重击",Status::Charge,1,2,
                                       "消耗20点法力，自身进入蓄力状态，后续造成2倍伤害",20);
    skills.push_back(heavyStrike);

    // 技能2：狂暴
    Skill* berserk = new buffSkill(2,"狂暴",Status::attackAdd,3,0.3,
                                   "消耗20点法力，攻击力增加30%",20);
    skills.push_back(berserk);
}

// 2. 剑士 - 巴尔（防御型剑士）
Barr::Barr(const std::string& name, int level)
    : Warrior(name, level) {

    // 技能1：盾击
    Skill* shieldBash = new buffSkill(1,"盾击",Status::Defend, 1, 0.5,
                                      "消耗20点法力，进入防御姿态，减伤50%，受到攻击后反击",20);
    skills.push_back(shieldBash);

    // 技能2：铁壁
    Skill* ironWall = new buffSkill(2,"铁壁",Status::defenseAdd, 1, 0.5,
                                    "消耗20点法力，防御力增加50%，持续1回合",20);
    skills.push_back(ironWall);
}

// 3. 法师 - 安娜（冰霜法师/治疗）
Anna::Anna(const std::string& name, int level)
    : Mage(name,level) {

    // 技能1：冰锥术
    Skill* iceSpike = new buffSkill(1,"冰锥术",Status::Asleep,2,2,
                                    "消耗50点法力，使敌人陷入两回合的睡眠状态",50);
    skills.push_back(iceSpike);

    // 技能2：治愈术（仅法师有治疗技能）
    Skill* healingTouch = new healSkill(2,"治愈术",50,0.5,
                                        "消耗50点法力，回复目标50%生命值");
    skills.push_back(healingTouch);
}

// 4. 法师 - 莉娜（火焰法师）
Lina::Lina(const std::string& name, int level)
    : Mage(name, level) {

    // 技能1：火球术
    Skill* fireball = new buffSkill(1,"火球术",Status::Poisoned,2,0.15,
                                    "消耗30点法力，使目标陷入持续2回合的中毒状态",30);
    skills.push_back(fireball);

    // 技能2：烈焰护体
    Skill* flameArmor = new buffSkill(2,"烈焰护体",Status::shieldAdd,2,0.3,
                                      "消耗30点法力，为目标施加护盾（生命值30%），护盾持续2个回合",30);
    skills.push_back(flameArmor);
}

// 5. 弓箭手 - 艾莉亚（神射手）
Arya::Arya(const std::string& name, int level)
    : Archer(name,level) {

    // 技能1：精准射击
    Skill* preciseShot = new buffSkill(1, "精准射击",Status::LifeSteal,2,0.3,
                                       "消耗30点法力，附加2回合的吸血效果",30);
    skills.push_back(preciseShot);

    // 技能2：鹰眼
    Skill* hawkeye = new buffSkill(2, "鹰眼",Status::critrateAdd,2,1.0,
                                   "消耗50点法力，增加自身100%的暴击率，持续2个回合",50);
    skills.push_back(hawkeye);
}

// 6. 弓箭手 - 罗宾（游侠）
Robin::Robin(const std::string& name, int level)
    : Archer(name,level) {

    // 技能1：毒箭
    Skill* poisonArrow = new buffSkill(1, "毒箭",Status::Poisoned,2,0.15,
                                       "消耗20点法力，对敌方施加2回合的中毒效果",20);
    skills.push_back(poisonArrow);

    // 技能2：疾风步
    Skill* windStep = new buffSkill(2, "疾风步",Status::missrateAdd,2,0.3,
                                    "消耗20点法力，增加0.3的闪避率，持续2回合",20);
    skills.push_back(windStep);
}

// 7. 无名之人 - 索拉（辅助型）
Sora::Sora(const std::string& name, int level)
    : Nonamer(name,level) {

    // 技能1：星光祝福
    Skill* starBlessing = new buffSkill(1, "星光祝福",Status::attackAdd, 3, 0.3,
                                        "消耗30点法力，使目标攻击力增强30%",30);
    skills.push_back(starBlessing);

    // 技能2：月之守护
    Skill* moonGuard = new buffSkill(2, "月之守护", Status::manaAdd, 3, 0.3,
                                     "使目标法力增强30%",0);
    skills.push_back(moonGuard);
}

// 8. 无名之人 - 无名的王（全能型）
NamelessKing::NamelessKing(const std::string& name, int level)
    : Nonamer(name,level) {

    // 技能1：王权
    Skill* sovereignty = new buffSkill(1, "王权",Status::Invincible, 2,0,
                                       "消耗70点法力，使目标处于两回合的无敌状态",70);
    skills.push_back(sovereignty);

    // 技能2：统御
    Skill* domination = new buffSkill(2, "统御",Status::critdamageAdd, 2, 0.3,
                                      "消耗30点法力，使目标的暴击伤害提升30%",30);
    skills.push_back(domination);
}
// 9. 格罗姆 - 狂战士
Gromm::Gromm(const std::string& name, int level)
    : Warrior(name, level) {
    // 技能1：嗜血狂暴
    Skill* bloodlust = new buffSkill(1, "嗜血狂暴", Status::LifeSteal, 2, 0.3, 
                                     "消耗20点法力进入狂暴状态，获得两回合30%吸血效果", 20);
    skills.push_back(bloodlust);
    
    // 技能2：无畏冲锋
    Skill* fearlessCharge = new buffSkill(2, "无畏冲锋", Status::attackAdd, 2, 0.3,
                                          "消耗20点法力，攻击力提高30%，持续2回合",20);
    skills.push_back(fearlessCharge);
}

// 10. 塞恩 - 守护骑士
Sion::Sion(const std::string& name, int level)
    : Warrior(name, level) {
    // 技能1：守护誓言
    Skill* guardianOath = new buffSkill(1, "守护誓言", Status::healthAdd, 2, 0.4,
                                        "消耗30点法力，自身生命值增加40%，持续2回合",30);
    skills.push_back(guardianOath);
    
    // 技能2：不屈意志
    Skill* unyieldingWill = new buffSkill(2, "不屈意志", Status::defenseAdd, 3, 0.6,
                                          "消耗30点法力，防御力提高60%，持续3回合",30);
    skills.push_back(unyieldingWill);
}

// 11. 亚瑟 - 圣骑士
Arthur::Arthur(const std::string& name, int level)
    : Warrior(name, level) {
    // 技能1：修养
    Skill* rest= new buffSkill(1, "休养", Status::fixed, 1, 0,
                                      "接下来的1回合内不消耗法力值", 0);
    skills.push_back(rest);
    
    // 技能2：王者祝福
    Skill* kingsBlessing = new buffSkill(2, "王者祝福", Status::attackAdd, 1, 1,
                                         "消耗50点法力值，攻击力增加100%，持续一回合", 50);
    skills.push_back(kingsBlessing);
}

// 12. 梅林 - 大法师
Merlin::Merlin(const std::string& name, int level)
    : Mage(name, level) {
    // 技能1：法力潮汐
    Skill* manaTide = new buffSkill(1, "法力潮汐", Status::manaAdd, 2, 0.4,
                                    "指定目标法力增加50%，持续2回合",0);
    skills.push_back(manaTide);
    
    // 技能2：时光停滞
    Skill* timeStop = new buffSkill(2, "时光停滞", Status::Paralyzed, 2, 0,
                                    "消耗50法力，使所有敌人麻痹2回合", 50);
    skills.push_back(timeStop);
}

// 13. 维嘉 - 暗影法师
Veigar::Veigar(const std::string& name, int level)
    : Mage(name, level) {
    // 技能1：暗影诅咒
    Skill* shadowCurse = new buffSkill(1, "暗影诅咒", Status::attackDec, 3, -0.3,
                                       "消耗30法力，降低敌人30%攻击力，持续3回合", 30);
    skills.push_back(shadowCurse);
    
    // 技能2：灵魂汲取
    Skill* soulSiphon = new healSkill(2, "灵魂汲取", 50, 0.3,
                                      "消耗50法力，恢复我方全体30%生命值");
    skills.push_back(soulSiphon);
}

// 14. 吉安娜 - 冰火法师
Jaina::Jaina(const std::string& name, int level)
    : Mage(name, level) {
    // 技能1：冰火两重天
    Skill* iceAndFire = new buffSkill(1, "冰火两重天", Status::Poisoned, 1, 0.15,
                                      "消耗50法力，敌人全体陷入中毒，持续一回合", 50);
    skills.push_back(iceAndFire);
    
    // 技能2：元素护盾
    Skill* elementalShield = new buffSkill(2, "元素护盾", Status::shieldAdd, 2, 0.2,
                                           "消耗50法力，为我方全体施加护盾，吸收20%生命值的伤害，持续2回合", 50);
    skills.push_back(elementalShield);
}

// 15. 温蕾萨 - 风行者
Vereesa::Vereesa(const std::string& name, int level)
    : Archer(name, level) {
    // 技能1：疾风射击
    Skill* windShot = new buffSkill(1, "疾风射击", Status::fastchange, 2, 0,
                                    "消耗20法力，为一个角色施加持续2回合的速切，该技能不消耗回合", 20);
    skills.push_back(windShot);
    
    // 技能2：风之庇护
    Skill* windSanctuary = new buffSkill(2, "风之庇护", Status::missrateAdd ,2, 0.3,
                                         "消耗30法力，使指定目标闪避率提高30%，持续2回合", 30);
    skills.push_back(windSanctuary);
}

// 16. 希尔瓦娜斯 - 游侠将军
Sylvanas::Sylvanas(const std::string& name, int level)
    : Archer(name, level) {
    // 技能1：黑暗箭雨
    Skill* darkArrowRain = new buffSkill(1, "黑暗箭雨", Status::Paralyzed, 2,0,
                                         "消耗30法力，对全体敌人附加麻痹效果，持续2回合", 30);
    skills.push_back(darkArrowRain);
    
    // 技能2：女王意志
    Skill* queenWill = new buffSkill(2, "女王意志", Status::Penetration, 2, 0,
                                     "消耗30点法力，使自身攻击附带穿透效果，持续两个回合", 30);
    skills.push_back(queenWill);
}

// 17. 莱戈拉斯 - 精灵射手
Legolas::Legolas(const std::string& name, int level)
    : Archer(name, level) {
    // 技能1：精准连射
    Skill* preciseVolley = new buffSkill(1, "精准连射", Status::critrateAdd, 3, 0.2,
                                         "消耗20法力，未来3个回合内攻击时，每次暴击率提高20%", 20);
    skills.push_back(preciseVolley);
    
    // 技能2：精灵之眼
    Skill* elvenEye = new buffSkill(2, "精灵之眼", Status::Penetration, 2, 0,
                                    "消耗30法力，为自身附加穿透，持续2回合", 30);
    skills.push_back(elvenEye);
}

// 18. 影 - 暗影者
Shadow::Shadow(const std::string& name, int level)
    : Nonamer(name, level) {
    // 技能1：暗影步
    Skill* shadowStep = new buffSkill(1, "暗影步", Status::missrateAdd, 2, 0.5,
                                      "消耗30法力，进入暗影状态，自身闪避率提高50%，持续2回合", 30);
    skills.push_back(shadowStep);
    
    // 技能2：背刺
    Skill* backstab = new buffSkill(2, "背刺", Status::critdamageAdd, 1, 0.8,
                                    "消耗30法力，暴击伤害提高80%，持续1回合，此次攻击必定暴击", 30);
    skills.push_back(backstab);
}

// 19. 光 - 光明使者
Light::Light(const std::string& name, int level)
    : Nonamer(name, level) {
    // 技能1：光明治愈
    Skill* lightHeal = new healSkill(1, "光明治愈", 40, 0.4,
                                     "消耗40法力，恢复目标40%生命值，移除目标所有负面状态");
    skills.push_back(lightHeal);
    
    // 技能2：神圣净化
    Skill* holyPurify = new buffSkill(2, "神圣净化", Status::Invincible, 1, 0,
                                      "消耗50法力，净化目标所有负面状态，使其无敌1回合", 50);
    skills.push_back(holyPurify);
}

// 20. 混沌 - 混沌行者
Chaos::Chaos(const std::string& name, int level)
    : Nonamer(name, level) {
    // 技能1：混沌波动
    Skill* chaosWave = new buffSkill(1, "混沌波动", Status::Asleep, 1, 0,
                                     "消耗50法力，使敌方目标休眠一个回合", 50);
    skills.push_back(chaosWave);
    
    // 技能2：命运骰子
    Skill* fateDice = new healSkill(2, "命运骰子",  20, 1,
                                    "消耗20法力，为随机一位队友回复100%的血量");
    skills.push_back(fateDice);
}
