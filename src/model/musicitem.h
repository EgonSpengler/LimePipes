#ifndef MUSICITEM_H
#define MUSICITEM_H

class MusicItem
{
public:
    MusicItem();
    virtual int type() const = 0;
};

#endif // MUSICITEM_H
