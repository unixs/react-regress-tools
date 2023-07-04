import parser from '../lib/deps_parser';

describe('deps parser', () => {

  it('is defined', () => {
    expect(parser.parser).toBeDefined();
  });

  it('is function', () => {
    expect(typeof parser.parser).toBe('function');
  });

  it('return promise', async () => {
    const result = parser.parser("test")
    expect(await result).toBe("test");
  }, 2000)
});
