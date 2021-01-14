
if (typeof WeakMap === "undefined" || typeof FinalizationRegistry == "undefined")
{
    window.jkeyweakmap = Map;
    window.jvalueweakmap = Map;
}
else
{
    function JKeyWeakMapCleanup(object)
    {
        object.c.delete(object.ref);
    }

    window.jkeyweakmap = function()
    {
        this.map = new WeakMap();
        this.rset = new Set();
        this.finalizationGroup = new FinalizationRegistry(JKeyWeakMapCleanup);

        this.set = function(key, value)
        {
            this.delete(key);
            const ref = new WeakRef(key);
            this.map.set(key, { value, ref });
            this.rset.add(ref);
            this.finalizationGroup.register(key, { c: this.rset, ref }, ref);
        }

        this.get = function(key)
        {
            const entry = this.map.get(key);
            return entry && entry.value;
        }

        this.delete = function(key)
        {
            const entry = this.map.get(key);
            if (!entry) return false;

            this.map.delete(key);
            this.rset.delete(entry.ref);
            this.finalizationGroup.unregister(entry.ref);
            return true;
        }

        this[Symbol.iterator] = function*()
        {
            for (const ref of this.rset)
            {
                const key = ref.deref();
                if (!key) continue;
                const { value } = this.map.get(key);
                yield [key, value];
            }
        }
    }

    function JValueWeakMapCleanup(object)
    {
        object.c.delete(object.key);
    }

    window.jvalueweakmap = function()
    {
        this.map = new Map();
        this.finalizationGroup = new FinalizationRegistry(JValueWeakMapCleanup);

        this.set = function(key, value)
        {
            this.delete(key);
            const ref = new WeakRef(value);
            this.map.set(key, ref);
            this.finalizationGroup.register(value, { c: this.map, key }, ref);
        }

        this.get = function(key)
        {
            const ref = this.map.get(key);
            if (!ref) return undefined;
            return ref.deref();
        }

        this.delete = function(key)
        {
            const ref = this.map.get(key);
            if (!ref) return false;

            this.map.delete(key);
            this.finalizationGroup.unregister(ref);
            return true;
        }

        this[Symbol.iterator] = function*()
        {
            for (const [key, ref] of this.map)
            {
                const value = ref.deref();
                if (!value) continue;
                yield [key, value];
            }
        }
    }
}

if (typeof TextDecoder !== "undefined")
    window.__TEXTDECODER = new TextDecoder("utf-8");

if (typeof TextEncoder !== "undefined")
    window.__TEXTENCODER = new TextEncoder("utf-8");

window.UTF8ArrayToString = function(array)
{
    if (window.__TEXTDECODER)
        return window.__TEXTDECODER.decode(array);

    var out, i, len, c;
    var char2, char3;

    out = [];
    len = array.length;
    i = 0;
    while(i < len)
    {
        c = array[i++];
        switch(c >> 4)
        {
        case 0: case 1: case 2: case 3: case 4: case 5: case 6: case 7:
            // 0xxxxxxx
            out.push(String.fromCharCode(c));
            break;
        case 12: case 13:
            // 110x xxxx   10xx xxxx
            char2 = array[i++];
            out.push(String.fromCharCode(((c & 0x1F) << 6) | (char2 & 0x3F)));
            break;
        case 14:
            // 1110 xxxx  10xx xxxx  10xx xxxx
            char2 = array[i++];
            char3 = array[i++];
            out.push(String.fromCharCode(((c & 0x0F) << 12) |
                        ((char2 & 0x3F) << 6) |
                        ((char3 & 0x3F) << 0)));
            break;
        }
    }

    return out.join('');
}

window.StringToUTF8Array = function(str)
{
    if (window.__TEXTENCODER)
        return window.__TEXTENCODER.encode(str);

    var array = new Array();

    var cc = 0;
    for(var i = 0, l = str.length; i < l; ++i)
    {
        cc = str.charCodeAt(i);
        if (cc > 0x80)
        {
            if (cc < 0x07FF)
            {
                array.push((cc >>>  6) | 0xC0);
                array.push((cc & 0x3F) | 0x80);
            }
            else
            {
                array.push((cc >>> 12)         | 0xE0);
                array.push(((cc >>>  6) & 0x3F) | 0x80);
                array.push((cc         & 0x3F) | 0x80);
            }
        }
        else
        {
            array.push(cc & 0xff);
        }
    }
    return new Uint8Array(array);
}