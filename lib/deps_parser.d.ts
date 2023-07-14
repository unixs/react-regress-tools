export interface IParserPayload {
  str: string;
}

declare const mod: {
  parser: (arg: IParserPayload) => Promise<string>
};

export default mod;
