#ifndef CHARACTER_CONFIG_H
#define CHARACTER_CONFIG_H

#include "weapon_config.h"
#include <string>
#include <vector>

// 前向声明
class Character;

// 枚举：角色职业
enum class CharacterClass {
    Warrior,    // 剑士
    Mage,       // 法师
    Archer,     // 弓箭手
    Nonamer,    //无名之人
};

//角色状态
enum class Status{
    attackAdd,                  //攻击增强
    defenseAdd,                 //防御增强
    attackDec,                  //攻击减少
    defenseDec,                 //防御减少
    healthAdd,                  //生命增加
    critrateAdd,                //暴击率增强
    critdamageAdd,              //暴击伤害增强
    manaAdd,                    //法力增强
    manaDec,                    //法力减少
    missrateAdd,                //闪避率增强
    shieldAdd,                  //附加护盾(固定为当前生命值的30%,可以抵消部分伤害)
    Penetration,                //穿透（无视护盾和防御）
    fastchange,                 //速切
    fixed,                      //不消耗魔法
    Normal,               //正常
    Defend,               //防御(减伤50%，受到攻击后反击，反击伤害为原伤害的50%)
    Charge,               //蓄力(需要一回合，随后打出两倍伤害)
    Poisoned,             // 中毒(固定消耗15%总生命值)
    Paralyzed,            // 麻痹
    Asleep,               // 睡眠
    Invincible,           //无敌(无法抵挡中毒)
    LifeSteal             //吸血(固定吸取本次造成有效伤害30%的血量）
};

//buff类
class buff{
public:
    Status buff_has;
    int bufftime;
    int buffvalue;
    buff(Status buff_has,int bufftime,int buffvalue):buff_has(buff_has),bufftime(bufftime),buffvalue(buffvalue){}
};

// 技能结构
class Skill {
protected:
    int id;                     // 技能ID
    std::string name;          // 技能名
    std::string description;   // 描述
    int manacost;               //法力消耗
public:
    Skill(int id,std::string name,int manacost,std::string description):id(id),name(name),manacost(manacost),description(description){}
    ~Skill()=default;
    int getmanacost(){return manacost;}
    std::string getname(){return name;}
    std::string getdescription(){return description;}
    virtual bool execute(Character* caster, Character* target);
};

class healSkill:public Skill{
protected:
    float healmount;              //治疗幅度
public:
    healSkill(int id,std::string name,int manacost,float healmount,std::string description):
        Skill(id,name,manacost,description),healmount(healmount){}
    bool execute(Character* caster, Character* target) override;
};

class buffSkill:public Skill{
protected:
    Status buff_add;              //施加buff类型
    int duringtime;               //持续时间
    float add;                      //增益幅度
public:
    buffSkill(int id, std::string name,Status buff_add,int duringtime,float add,std::string description,int manacost=0):
        Skill(id,name,manacost,description),
        buff_add(buff_add),duringtime(duringtime),add(add){}
    bool execute(Character* caster, Character* target) override;
};

// 基类：角色
class Character {
protected:
    std::string name;           // 角色名
    CharacterClass job;         // 职业
    int level;                  // 等级
    int health;                 // 生命值
    int healthadd;              //生命值增加值
    int maxHealth;              // 最大生命值
    int attack;                 // 攻击力
    int attackadd;              //攻击力增加
    int defense;                // 防御力
    int defenseadd;             //防御力增加
    int maxmana;                // 最大魔法值
    int mana;                   //魔法值
    int manaadd;                //魔法值增加
    float critrate;             // 暴击率
    float critrateadd;          //暴击率增加
    float critdamage;           // 暴击伤害
    float critdamageadd;        //暴击伤害增加
    float missrate;             //闪避率
    float missrateadd;          //闪避率增加
    int shield;                 //护盾值
    bool isalive;               //是否存活
    bool isFrontline;           //是否站场
    int turnCount;                     // 战斗回合数
    int currentSkillIndex;             // 当前技能索引
    Weapon* equippedWeapon; //装备的武器
    std::vector<Skill*> skills;    // 技能列表
    std::vector<buff> buffs;      //含有的buff

public:
    // 构造函数
    Character(const std::string& name, CharacterClass job, int level = 1,
              float critrate=0.2,float critdamage=1.0, float missrate=0,
              int shield=0,bool isalive=true,bool isFrontline=false);

    // 虚析构函数
    virtual ~Character() = default;

    // 获取属性
    std::string getName() const { return name; }
    CharacterClass getJob() const { return job; }
    int getLevel() const { return level; }
    int getHealth() const { return health; }
    int gethealthadd() const {return healthadd;}
    int getattackadd() const {return attackadd;}
    int getdefenseadd() const {return defenseadd;}
    float getcritrateadd() const {return critrateadd;}
    float getcritdamageadd() const {return critdamageadd;}
    float getmissrateadd() const {return missrateadd;}
    int getMaxHealth() const { return maxHealth; }
    int getAttack() const {return attack;}
    int getDefense() const {return defense;}
    int getmaxmana() const { return maxmana; }
    int getmana() const {return mana;}
    int getmanaadd() const {return manaadd;}
    float getCritrate() const { return critrate; }
    float getCritdamage() const {return critdamage;}
    float getMissrate() const {return missrate;}
    int getShield() const {return shield;}
    bool alive() const {return isalive;}
    bool isFront() const { return isFrontline; }
    int getTurnCount() const { return turnCount; }
    int getcurrentSkillIndex() const {return currentSkillIndex;}
    const Weapon* getWeapon() const {return equippedWeapon;}
    const std::vector<Skill*>& getSkills() const { return skills; }
    const std::vector<buff>& getbuffs() const {return buffs;}


    // 设置属性
    void setWeapon(Weapon* weapon);
    void removeWeapon();
    void setName(const std::string& newname) { name = newname; }
    void setFrontline() { isFrontline = true; }
    void setcurrentSkillIndex(int current) {currentSkillIndex =current;}
    void addSkill(Skill* skill);
    void addbuff(const buff& buff);
    bool useSkill(int skillIndex,Character* target);
    bool startTurn();
    void endTurn();
    void setLevel(int newlevel) { level=newlevel; }
    void setHealth(int damage) { health-=damage; }
    void sethealthadd(int add) {healthadd=add;}
    void setattackadd(int add) {attackadd=add;}
    void setdefenseadd(int add) {defenseadd=add;}
    void setcritrateadd(float add) {critrateadd=add;}
    void setcritdamageadd(float add) {critdamageadd=add;}
    void setmissrateadd(float add) {missrateadd=add;}
    void setMaxHealth(int newmaxhealth) {maxHealth=newmaxhealth; }
    void setAttack(int newattack) {attack=newattack;}
    void setDefense(int newdefense){defense=newdefense;}
    void setmaxmana(int newmaxmana) {maxmana=newmaxmana;}
    void setmana(int newmana) {mana=newmana;}
    void setmanaadd(int add) {manaadd=add;}
    void setCritrate(float newcritrate) { critrate=newcritrate; }
    void setCritdamage(float newcritdamage) {critdamage=newcritdamage;}
    void setMissrate(float newmissrate) {missrate=newmissrate;}
    void setShield(int newshield) {shield=newshield;}
    void setalive(bool newalive) {isalive=newalive;}
    void setisFront(bool front) {isFrontline=front; }
    void setTurnCount(int turn) {turnCount=turn; }


    // 战斗相关方法
    virtual void takeDamage(int damage);
    virtual void heal(int amount);

    // 升级
    virtual void levelUp();

    // 显示信息
    virtual std::string getInfo() const;
    virtual std::string getJobName() const;

};

// 具体角色类：剑士
class Warrior : public Character {
public:
    Warrior(const std::string& name, int level = 1);
    // 重写基类方法
    void levelUp() override;
};

// 具体角色类：法师
class Mage : public Character {
public:
    Mage(const std::string& name, int level = 1);
    // 重写基类方法
    void levelUp() override;
};

// 具体角色类：弓箭手
class Archer : public Character {
public:
    Archer(const std::string& name, int level = 1);

    // 重写基类方法
    void levelUp() override;
};

// 具体角色类：无名之人
class Nonamer : public Character {
public:
    Nonamer(const std::string& name, int level = 1);
    // 重写基类方法
    void levelUp() override;
};

// 角色管理器
class CharacterManager {
private:
    std::vector<Character*> characters;

public:
    // 添加角色
    void addCharacter(Character* character);

    // 查找角色
    Character* findCharacter(const std::string& name) const;

    // 获取所有角色
    std::vector<Character*> getAllCharacters() const { return characters; }

    // 移除角色
    bool removeCharacter(const std::string& name);

    // 保存/加载角色
    bool saveToFile(const std::string& filename) const;
    bool loadFromFile(const std::string& filename);
    ~CharacterManager(){
        for(int i=0;i<characters.size();i++){
            delete characters[i];
        }
    }
};

//具体角色
// 1. 剑士 - 莱昂
class Leon : public Warrior {
public:
    Leon(const std::string& name = "莱昂", int level = 1);
    std::string getJobName() const override { return "剑士"; }
};

// 2. 剑士 - 巴尔
class Barr : public Warrior {
public:
    Barr(const std::string& name = "巴尔", int level = 1);
    std::string getJobName() const override { return "剑士"; }
};

// 3. 法师 - 安娜
class Anna : public Mage {
public:
    Anna(const std::string& name = "安娜", int level = 1);
    std::string getJobName() const override { return "法师"; }
};

// 4. 法师 - 莉娜
class Lina : public Mage {
public:
    Lina(const std::string& name = "莉娜", int level = 1);
    std::string getJobName() const override { return "法师"; }
};

// 5. 弓箭手 - 艾莉亚
class Arya : public Archer {
public:
    Arya(const std::string& name = "艾莉亚", int level = 1);
    std::string getJobName() const override { return "弓箭手"; }
};

// 6. 弓箭手 - 罗宾
class Robin : public Archer {
public:
    Robin(const std::string& name = "罗宾", int level = 1);
    std::string getJobName() const override { return "弓箭手"; }
};

// 7. 无名之人 - 索拉
class Sora : public Nonamer {
public:
    Sora(const std::string& name = "索拉", int level = 1);
    std::string getJobName() const override { return "无名之人"; }
};

// 8. 无名之人 - 无名的王
class NamelessKing : public Nonamer {
public:
    NamelessKing(const std::string& name = "无名的王", int level = 1);
    std::string getJobName() const override { return "无名之人"; }
};

// 9. 剑士 - 格罗姆
class Gromm : public Warrior {
public:
    Gromm(const std::string& name = "格罗姆", int level = 1);
    std::string getJobName() const override { return "剑士"; }
};

// 10. 剑士 - 塞恩
class Sion : public Warrior {
public:
    Sion(const std::string& name = "塞恩", int level = 1);
    std::string getJobName() const override { return "剑士"; }
};

// 11. 剑士 - 亚瑟
class Arthur : public Warrior {
public:
    Arthur(const std::string& name = "亚瑟", int level = 1);
    std::string getJobName() const override { return "剑士"; }
};

// 12. 法师 - 梅林
class Merlin : public Mage {
public:
    Merlin(const std::string& name = "梅林", int level = 1);
    std::string getJobName() const override { return "法师"; }
};

// 13. 法师 - 维嘉
class Veigar : public Mage {
public:
    Veigar(const std::string& name = "维嘉", int level = 1);
    std::string getJobName() const override { return "法师"; }
};

// 14. 法师 - 吉安娜
class Jaina : public Mage {
public:
    Jaina(const std::string& name = "吉安娜", int level = 1);
    std::string getJobName() const override { return "法师"; }
};

// 15. 弓箭手 - 温蕾萨
class Vereesa : public Archer {
public:
    Vereesa(const std::string& name = "温蕾萨", int level = 1);
    std::string getJobName() const override { return "弓箭手"; }
};

// 16. 弓箭手 - 希尔瓦娜斯
class Sylvanas : public Archer {
public:
    Sylvanas(const std::string& name = "希尔瓦娜斯", int level = 1);
    std::string getJobName() const override { return "弓箭手"; }
};

// 17. 弓箭手 - 莱戈拉斯
class Legolas : public Archer {
public:
    Legolas(const std::string& name = "莱戈拉斯", int level = 1);
    std::string getJobName() const override { return "弓箭手"; }
};

// 18. 无名之人- 影
class Shadow : public Nonamer {
public:
    Shadow(const std::string& name = "影", int level = 1);
    std::string getJobName() const override { return "无名之人"; }
};

// 19. 无名之人 - 光
class Light : public Nonamer {
public:
    Light(const std::string& name = "光", int level = 1);
    std::string getJobName() const override { return "无名之人"; }
};

// 20. 无名之人 - 混沌
class Chaos : public Nonamer {
public:
    Chaos(const std::string& name = "混沌", int level = 1);
    std::string getJobName() const override { return "无名之人"; }
};


#endif // CHARACTER_CONFIG_H
