
if (typeof WeakMap === "undefined" || typeof FinalizationRegistry == "undefined")
{
    window.jkeyweakmap = Map;
    window.jvalueweakmap = Map;
}
else
{
    function JKeyWeakMapCleanup(iter)
    {
        for (var object of iter)
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

    function JValueWeakMapCleanup(iter)
    {
        for (var object of iter)
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

